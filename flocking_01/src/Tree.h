#pragma once

#include "boid.h"
#include "assert.h"

#define maxParticles 4

class Tree {
public:
	// 0 approximates everything
	// 1 is exact within leaves
	// 2 is exact with adjacent leaves
    static constexpr float accuracy = 0.5;

	bool empty;
	int nParticles;
	boid* particles[maxParticles];
	bool hasChildren;
	Tree *nw, *ne, *sw, *se;
	float minX, minY, midX, midY, maxX, maxY, side;
    float x, y, mass;

	Tree() :
		empty(true),
		nParticles(0),
		hasChildren(false),
		minX(0), minY(0),
		midX(0), midY(0),
		maxX(0), maxY(0) {
	}
	Tree(float _minX, float _minY, float _maxX, float _maxY) :
		empty(true),
		nParticles(0),
		hasChildren(false),
		minX(_minX), minY(_minY),
		maxX(_maxX), maxY(_maxY) {
		setMid();
	}
	~Tree() {
		if(hasChildren) {
			delete nw;
			delete ne;
			delete sw;
			delete se;
		}
	}
	void setMid() {
		midX = (minX + maxX) / 2;
		midY = (minY + maxY) / 2;
		side = maxX - minX;
	}
	void findBoundaries(vector<boid>& all) {
		minX = all[0].position.x;
		minY = all[0].position.y;
		maxX = minX;
		maxY = minY;
		int n = all.size();
		for(int i = 0; i < n; i++) {
			if(all[i].position.x < minX)
				minX = all[i].position.x;
			if(all[i].position.y < minY)
				minY = all[i].position.y;
			if(all[i].position.x > maxX)
				maxX = all[i].position.x;
			if(all[i].position.y > maxY)
				maxY = all[i].position.y;
		}
		setMid();
	}
	void squareBoundaries() {
		float centerX = (minX + maxX) / 2;
		float centerY = (minY + maxY) / 2;
		float diffX = maxX - minX;
		float diffY = maxY - minY;
		float halfSide = max(diffX, diffY) / 2;
		minX = centerX - halfSide;
		maxX = centerX + halfSide;
		minY = centerY - halfSide;
		maxY = centerY + halfSide;
		setMid();
	}
	void add(boid& cur) {
		if(hasChildren) {
			if(cur.position.x < midX) {
				if(cur.position.y < midY) {
					nw->add(cur);
				} else {
					sw->add(cur);
				}
			} else {
				if(cur.position.y < midY) {
					ne->add(cur);
				} else {
					se->add(cur);
				}
			}
		} else {
			if(nParticles < maxParticles) {
				particles[nParticles] = &cur;
				nParticles++;
                mass += cur.mass;
				empty = false;
			} else {
				nw = new Tree(minX, minY, midX, midY);
				ne = new Tree(midX, minY, maxX, midY);
				sw = new Tree(minX, midY, midX, maxY);
				se = new Tree(midX, midY, maxX, maxY);
				hasChildren = true;
				for(int i = 0; i < nParticles; i++)
					add(*particles[i]);
				nParticles = 0;
				add(cur);
			}
		}
	}
	void addAll(vector<boid>& all) {
		int n = all.size();
		for(int i = 0; i < n; i++)
			add(all[i]);
	}
	void findCenterOfMass() {
		if(hasChildren) {
			nw->findCenterOfMass();
			ne->findCenterOfMass();
			sw->findCenterOfMass();
			se->findCenterOfMass();
            mass +=
                nw->mass +
                ne->mass +
                sw->mass +
                se->mass;
			x +=
				nw->x * nw->mass +
				ne->x * ne->mass +
				sw->x * sw->mass +
				se->x * se->mass;
			x /= mass;
			y +=
				nw->y * nw->mass +
				ne->y * ne->mass +
				sw->y * sw->mass +
				se->y * se->mass;
			y /= mass;
		} else {
			if(nParticles) {
				for(int i = 0; i < nParticles; i++) {
					boid& cur = *particles[i];
					x += cur.position.x * cur.mass;
					y += cur.position.y * cur.mass;
					mass += cur.mass;
				}
				x /= mass;
				y /= mass;
			}
		}
	}
	void build(vector<boid>& particles) {
		findBoundaries(particles);
		squareBoundaries();
		addAll(particles);
		findCenterOfMass();
	}
	void sumForces(boid& cur) {
		if(!empty) {
			float xd = x - cur.position.x;
			float yd = y - cur.position.y;
			float rsq = xd * xd + yd * yd;
			if(rsq > 0) {
				if(sqrtf(rsq) / side > accuracy) {
					// far away, approximate
					float mor3 = mass / rsq;
					cur.acceleration.x += xd * mor3;
					cur.acceleration.y += yd * mor3;
				} else if(nParticles) {
					// too close, sum particles
					//ofSetColor(255, 0, 0);
					//ofRect(minX, minY, side, side);
					for(int i = 0; i < nParticles; i++) {
						boid& target = *particles[i];
/*
						// if you move .update() to draw(), uncomment to watch
						// connections drawn between exact calculations
						ofSetColor(0, 0, 128);
						ofLine(cur.x, cur.y, (target.x + cur.x) / 2, (target.y + cur.y) / 2);
						ofSetColor(0, 0, 255);
						ofLine((target.x + cur.x) / 2, (target.y + cur.y) / 2, target.x, target.y);
*/
						if(&target != &cur) {
							xd = target.position.x - cur.position.x;
							yd = target.position.y - cur.position.y;
							rsq = xd * xd + yd * yd;
							float mor3 = target.mass / rsq;
							cur.acceleration.x += xd * mor3;
							cur.acceleration.y += yd * mor3;
						}
					}
				} else {
					// too close, go deeper
					nw->sumForces(cur);
					ne->sumForces(cur);
					sw->sumForces(cur);
					se->sumForces(cur);
				}
			}
		}
	}
	void draw() {
		ofRect(minX, minY, maxX - minX, maxY - minY);
		if(hasChildren) {
			nw->draw();
			ne->draw();
			sw->draw();
			se->draw();
		}
	}
};
