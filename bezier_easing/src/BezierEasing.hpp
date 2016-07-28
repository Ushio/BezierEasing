//
//  BezierEasing.hpp
//  bezier_easing
//
//  Created by Nakazi_w0w on 7/28/16.
//
//

#pragma once

#include <vector>

// intermediate_points = number of intermediate points
class BezierEasing {
public:
    BezierEasing(double cx0, double cy0, double cx1, double cy1, int intermediate_points) {
        intermediate_points = std::max(intermediate_points, 1);
        
        cx0 = std::max(cx0, 0.0);
        cx0 = std::min(cx0, 1.0);
        
        _pivots.reserve(intermediate_points - 1);
        double step = 1.0 / intermediate_points;
        for(int i = 1; i < intermediate_points ; ++i) {
            double t = step * i;
            double t2 = t * t;
            double t3 = t2 * t;
            
            double one_minus_t = 1.0 - t;
            double one_minus_t2 = one_minus_t * one_minus_t;
            double x = 3.0 * (one_minus_t2 * t * cx0 + one_minus_t * t2 * cx1) + t3;
            double y = 3.0 * (one_minus_t2 * t * cy0 + one_minus_t * t2 * cy1) + t3;
            _pivots.emplace_back(x, y);
        }
    }
    double lerp(double a, double b, double amt) {
        return a + (b - a) * amt;
    }
    double evaluate(double x) {
        x = std::max(x, 0.0);
        x = std::min(x, 1.0);
        
        auto rhs = std::upper_bound(_pivots.begin(), _pivots.end(), std::make_pair(x, 0.0), [](const std::pair<double, double> &a, const std::pair<double, double> &b) {
            return a.first < b.first;
        });
        
        if(rhs == _pivots.end()) {
            auto tail = _pivots[_pivots.size() - 1];
            auto amt = (x - tail.first) / (1.0 - tail.first);
            return lerp(tail.second, 1.0, amt);
        }
        if(rhs == _pivots.begin()) {
            auto head = _pivots[0];
            auto amt = x / head.first;
            return head.second * amt;
        }
        
        auto lhs = std::prev(rhs);
        auto amt = (x - lhs->first) / (rhs->first - lhs->first);
        return lerp(lhs->second, rhs->second, amt);
    }
    
    std::vector<std::pair<double, double>> _pivots;
};