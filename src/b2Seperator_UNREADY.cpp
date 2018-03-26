#include "b2Seperator.h"

b2Seperator::b2Seperator() {
}

b2Seperator::~b2Seperator() {
}

void b2Seperator::Seperate(b2Body* body, b2FixtureDef* fixtureDef, std::vector<b2Vec2>& verticesVec, float scale) {
    int i = 0;
    int n = verticesVec.size();
    int j = 0;
    int m = 0;
    std::vector<b2Vec2> vec;
    std::vector<std::vector<b2Vec2>> figsVec;
    b2PolygonShape polyShape;

    for(i = 0; i < n; i++) {
        vec.push_back(b2Vec2(verticesVec[i].x * scale, verticesVec[i].y * scale));
    }

    figsVec = this->calcShapes(vec);
    n = figsVec.size();

    for(i = 0; i < n; i++) {
        verticesVec = std::vector<b2Vec2>();
        vec = figsVec[i];
        m = vec.size();
        for(j = 0; j < m; j++) {
            verticesVec.push_back(b2Vec2(vec[j].x / scale, vec[j].y / scale));
        }

        polyShape = b2PolygonShape();
        polyShape.Set(&verticesVec[0], verticesVec.size());
        fixtureDef->shape = &polyShape;
        body->CreateFixture(fixtureDef);
    }
}

int b2Seperator::Validate(std::vector<b2Vec2>& verticesVec) {
    int i = 0;
    int n = verticesVec.size();
    int j = 0;
    int j2 = 0;
    int i2 = 0;
    int i3 = 0;
    float d = 0;
    int ret = 0;

    bool fl = false, fl2 = false;

    for(i = 0; i < n; i++) {
        i2 = (i < n - 1) ? i + 1 : 0;
        i3 = (i > 0) ? i - 1 : n - 1;

        fl = false;
        for(j = 0; j < n; j++) {
            if(((j != i) && j != i2)) {
                if(!fl) {
                    d = this->det(verticesVec[i].x, verticesVec[i].y, verticesVec[i2].x, verticesVec[i2].y, verticesVec[j].x, verticesVec[j].y);
                    if(d > 0) {
                        fl = true;
                    }
                }

                if(j != i3) {
                    j2 = (j < n - 1) ? j + 1 : 0;
                    if(this->hitSegment(verticesVec[i].x, verticesVec[i].y, verticesVec[i2].x, verticesVec[i2].y, verticesVec[j].x, verticesVec[j].y, verticesVec[j2].x, verticesVec[j2].y)) {
                        ret = 1;
                    }
                }
            }
        }

        if(!fl) {
            fl2 = true;
        }
    }

    if(fl2) {
        if(ret == 1) {
            ret = 3;
        } else {
            ret = 2;
        }
    }

    return ret;
}

void b2Seperator::calcShapes(std::vector<b2Vec2>& verticesVec, std::vector<std::vector<b2Vec2>>& figsVec) {
    std::vector<b2Vec2> vec;
    int i = 0;
    int n = 0;
    int j = 0;
    float d = 0, t = 0, dx = 0, dy = 0, minLen = 0;
    int i1 = 0, i2 = 0, i3 = 0;
    b2Vec2 p1, p2, p3;
    int j1 = 0, j2 = 0;
    b2Vec2 v1, v2;
    int k = 0, h = 0;

    std::vector<b2Vec2> vec1, vec2;
    b2Vec2 v, hitV;
    bool isConvex = false;

    std::vector<std::vector<b2Vec2>> queue;
}
