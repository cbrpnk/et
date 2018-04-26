#pragma once

using namespace Et::Math;
using namespace Et::Test;

unsigned int TEST_FUNCTIONS() {
    Unit unit("Functions");
    
    unit.add("min", []() {
        eq({{min(-1, -2), -2}, {min(-1, 2), -1}, {min(1, 2), 1}});
    });
    
    unit.add("max", []() {
        eq({{max(-1, -2), -1}, {max(-1, 2), 2}, {max(1, 2), 2}});
    });
    
    unit.add("clamp", []() {
        eq({{clamp(-10, 0, 10), 0}, {clamp(4, 0, 10), 4}, {clamp(20, 0, 10), 10}});
    });
    
    unit.add("map", []() {
        eq({
            {map(2, 0, 4, 0, 100), 50},
            {map(-1, -20, 0, 0, 100), 95},
            {map(0, -100, 100, 0, 4), 2}
        });
    });
    
    unit.add("solveQuadratic", []() {
        QuadraticResult x = solveQuadratic(3, 4, -4);
        float eps = 0.001;
        eq({x.hasRoots, true});
        eq({x.minus, -2.0f}, "Minus root");
        gt(x.plus, 0);
        lt(x.plus-0.666, eps, "Plus root");
    });
    
    return unit.run();
}
