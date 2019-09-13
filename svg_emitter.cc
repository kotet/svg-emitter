#include <string>
#include <cstdint>
#include <boost/format.hpp>
#include <boost/algorithm/string.hpp>

#include "svg_emitter.hpp"

using std::string;
using std::to_string;
using std::vector;

namespace svg
{

SVG::SVG(uint64_t width, uint64_t height)
{
    this->width = width;
    this->height = height;
    this->svg_elements = vector<SVGElement>();
}

SVGAttribute::SVGAttribute(std::string key, std::string value)
{
    this->key = key;
    this->value = value;
}

SVGElement::SVGElement(std::string name)
{
    this->name = name;
}

void SVG::stroke_custom(SVGElement element)
{
    this->svg_elements.push_back(element);
}

void SVG::stroke_circle(double cx, double cy, double r, std::string stroke_color, double stroke_width)
{
    SVGElement circle = SVGElement("circle");
    circle.attributes.push_back(SVGAttribute("cx", to_string(cx + this->width / 2)));
    circle.attributes.push_back(SVGAttribute("cy", to_string(cy + this->height / 2)));
    circle.attributes.push_back(SVGAttribute("r", to_string(r)));
    circle.attributes.push_back(SVGAttribute("stroke", stroke_color));
    circle.attributes.push_back(SVGAttribute("stroke-width", to_string(stroke_width)));
    this->stroke_custom(circle);
}

void SVG::stroke_line(double x1, double y1, double x2, double y2, std::string stroke_color, double stroke_width)
{
    SVGElement line = SVGElement("line");
    line.attributes.push_back(SVGAttribute("x1", to_string(x1 + this->width / 2)));
    line.attributes.push_back(SVGAttribute("y1", to_string(y1 + this->height / 2)));
    line.attributes.push_back(SVGAttribute("x2", to_string(x2 + this->width / 2)));
    line.attributes.push_back(SVGAttribute("y2", to_string(y2 + this->height / 2)));
    line.attributes.push_back(SVGAttribute("stroke", stroke_color));
    line.attributes.push_back(SVGAttribute("stroke-width", to_string(stroke_width)));
    this->stroke_custom(line);
}

string SVG::emit_svg()
{
    string svgstr = (boost::format(R"###(<svg style="border: 1px solid black" width="%d" height="%d" fill="none">)###") % this->width % this->height).str();
    for (SVGElement elm : this->svg_elements)
    {
        svgstr.append("<");
        svgstr.append(elm.name);
        for (SVGAttribute attr : elm.attributes)
        {
            svgstr.append((boost::format(R"###( %s="%s")###") % attr.key % attr.value).str());
        }
        svgstr.append((boost::format(R"###(></%s>)###") % elm.name).str());
    }

    svgstr.append("</svg>");
    return svgstr;
}

string SVG::emit_html(string message)
{
    string html = R"###(<!DOCTYPE html><html><body>)###";
    html.append(this->emit_svg());
    boost::replace_all(message, "\n", "<br/>");
    html.append((boost::format(R"###(<p>%s</p>)###") % message).str());
    html.append("</body></html>");
    return html;
}

}