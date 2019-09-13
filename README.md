# svg-emitter
Simple svg emitter for debugging

```cpp
#include <iostream>
#include "svg_emitter.hpp"

int main()
{
    svg::SVG s = svg::SVG(400, 300);
    s.stroke_circle(0, 0, 100, "blue", 10);
    s.stroke_line(0, 0, 100, 100);
    std::cout << s.emit_html("this\nis\ntest") << std::endl;
    return 0;
}
```

```html
<!DOCTYPE html><html><body><svg style="border: 1px solid black" width="400" height="300" fill="none"><circle cx="200.000000" cy="150.000000" r="100.000000" stroke="blue" stroke-width="10.000000"></circle><line x1="200.000000" y1="150.000000" x2="300.000000" y2="250.000000" stroke="black" stroke-width="1.000000"></line></svg><p>this<br/>is<br/>test</p></body></html>
```
