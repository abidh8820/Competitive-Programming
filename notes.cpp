// finding the nearest equal or greater value
auto y = lower_bound(a.begin(), a.end(), x);
// finding the nearest equal or lesser value
auto y = --upper_bound(a.begin(), a.end(), x);
