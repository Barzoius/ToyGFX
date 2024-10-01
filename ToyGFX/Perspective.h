#pragma once


class Perspective
{

};

class Orthographic
{

};

class Curvilinear
{

};

template <typename ProjectionType>
class Projection : public ProjectionType
{


};