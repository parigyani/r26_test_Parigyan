#include <iostream>
#include <fstream>
#include <vector>

struct GPSData {
    double latitude;
    double longitude;
};

GPSData decodeUBX(const std::vector<uint8_t>& buffer) {
    // Assuming UBX-NAV-PVT format
    int latIndex = 30; // bytes 30–33
    int lonIndex = 34; // bytes 34–37

    int32_t lat_raw = *(int32_t*)&buffer[latIndex];
    int32_t lon_raw = *(int32_t*)&buffer[lonIndex];

    GPSData data;
    data.latitude = lat_raw / 1e7;
    data.longitude = lon_raw / 1e7;
    return data;
}

int main() {
    std::ifstream file("gps_data.ubx", std::ios::binary);
    std::vector<uint8_t> buffer((std::istreambuf_iterator<char>(file)), {});
    GPSData gps = decodeUBX(buffer);
    std::cout << "Latitude: " << gps.latitude << ", Longitude: " << gps.longitude << std::endl;
    return 0;
}