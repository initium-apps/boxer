#ifndef B2SEPERATOR_H
#define B2SEPERATOR_H

/*
* Port of "Convex Separator for Box2D Flash" to C++11.
*
* This class has been written by Antoan Angelov.
* It is designed to work with Erin Catto's Box2D physics library.
*
* Everybody can use this software for any purpose, under two restrictions:
* 1. You cannot claim that you wrote this software.
* 2. You can not remove or alter this notice.
*
*/
class b2Seperator {
    public:
        b2Seperator();
        virtual ~b2Seperator();

        void Seperate(b2Body*, b2FixtureDef*, std::vector<b2Vec2>&, float);
        int Validate(std::vector<b2Vec2>&);
    private:
        std::vector<std::vector<b2Vec2>> calcShapes(std::vector<b2Vec2>&);
        b2Vec2 hitRay(float, float, float, float, float, float, float, float);
        b2Vec2 hitSegment(float, float, float, float, float, float, float, float);
        bool isOnSegment(float, float, float, float, float, float);
        bool pointsMatch(float, float, float, float);
        bool isOnLine(float, float, float, float, float, float);
        float det(float, float, float, float, float, float);

        void err();
};

#endif // B2SEPERATOR_H
