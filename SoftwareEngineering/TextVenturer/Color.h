#pragma once

struct Color
{
    float r, g, b, a;

    Color(float r, float g, float b, float a = 1);
    Color();

    static Color HSV(float h, float s, float v, float a = 1);
    void toHSV(float & h, float & s, float & v);

    static Color rainbow(float hue, float a = 1);
    Color addRainbow(float amount);

    bool operator==(const Color other) const;

    const static std::unordered_map<std::string, Color> dictionary;

    Color operator*(float v) const;
    friend Color operator*(float v, const Color & color);
};

