#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace svg
{

class SVGAttribute
{
public:
    std::string key;
    std::string value;
    SVGAttribute(std::string key, std::string value);
};

class SVGElement
{
public:
    std::vector<SVGAttribute> attributes;
    std::string name;
    SVGElement(std::string name);
};

class SVG
{
private:
    uint64_t width;
    uint64_t height;
    std::vector<SVGElement> svg_elements;

public:
    SVG(uint64_t width, uint64_t height);
    std::string emit_svg();
    std::string emit_html(std::string message);
    void stroke_custom(SVGElement element);
    void stroke_circle(double cx, double cy, double r, std::string stroke_color = "black", double stroke_width = 1);
    void stroke_line(double x1, double y1, double x2, double y2, std::string stroke_color = "black", double stroke_width = 1);
};

}