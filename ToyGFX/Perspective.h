#pragma once


//class Perspective
//{
//
//};
//
//class Orthographic
//{
//
//};
//
//class Curvilinear
//{
//
//};

#include <vector>
#include <memory>
#include <string>
//template <typename ProjectionType>
//class Projection : public ProjectionType
//{
//
//    
//};


class Proj
{
public:
    virtual std::string project()  = 0; 
    virtual ~Proj() = default; 
};


class Perspective : public Proj
{
public:
    std::string msg;
    std::string project() override {
        msg = "Perspective projection";
        return msg;
    }
};

class Orthographic : public Proj
{
public:
    std::string msg;
    std::string project() override {
        msg = "Ortho projection";
        return msg;
    }
};

class Curvilinear : public Proj
{
    std::string msg;
    std::string project() override {
        msg = "Curvi projection";
        return msg;
    }
};


class Projection
{
private:
    std::unique_ptr<Proj> projection; 
    
public:
    std::string mssg;

    template <typename ProjectionType>
    Projection(std::unique_ptr<ProjectionType> p) : projection(std::move(p)) {}

    template <typename ProjectionType>
    void setProjection(std::unique_ptr<ProjectionType> p) {
        projection = std::move(p);
    }


    void doProjection()  {
        mssg = projection.get() -> project();
    }
};