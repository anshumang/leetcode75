int largestAltitude(vector<int>& gain) {
    int max_altitude = 0, current = 0;
    for (int g : gain) {
        current += g;
        max_altitude = max(max_altitude, current);
    }
    return max_altitude;
}
