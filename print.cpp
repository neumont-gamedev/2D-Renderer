Canvas canvas(renderer, width, height);
Image image1;
image1.Load("cat.bmp");

Image image2;
image2.Load("sus.bmp");

Image image3;
image3.Load("color.bmp", 155);

canvas.DrawImage(&image, { 100, 100 });
canvas.DrawImage(&image2, { 300, 300 }, { 0, 255, 0, 255 });
canvas.DrawImageAlpha(&image3, { 200, 200 });

void DrawImage(const class Image* image, const SDL_Point& point, const SDL_Color& key);
void Canvas::DrawImage(const Image* image, const SDL_Point& point, const SDL_Color& key)
{
    pixel_t pixelKey = ColorToPixel(key);
    for (int y = 0; y < image->m_height; y++)
    {
        int sy = point.y + y;
        for (int x = 0; x < image->m_width; x++)
        {
            int sx = point.x + x;
            if (sx < 0 || sx >= m_width || sy < 0 || sy >= m_height) continue;

            pixel_t pixel = image->m_buffer[x + (y * image->m_width)];
            if (pixel == pixelKey) continue; // discard

            m_buffer[sx + (sy * m_width)] = pixel;
        }
    }
}

void DrawImageAlpha(const class Image* image, const SDL_Point& point);
void Canvas::DrawImageAlpha(const Image* image, const SDL_Point& point)
{
    for (int y = 0; y < image->m_height; y++)
    {
        int sy = point.y + y;
        for (int x = 0; x < image->m_width; x++)
        {
            int sx = point.x + x;
            if (sx < 0 || sx >= m_width || sy < 0 || sy >= m_height) continue;

            SDL_Color dstColor = PixelToColor(m_buffer[sx + (sy * m_width)]);
            SDL_Color srcColor = PixelToColor(image->m_buffer[x + (y * image->m_width)]);

            // color = (source color * source alpha) + (destination color * (1 - source alpha))

            float a = (srcColor.a / 255.0f);
            srcColor.r = (Uint8)(srcColor.r * a);
            srcColor.g = (Uint8)(srcColor.g * a);
            srcColor.b = (Uint8)(srcColor.b * a);

            dstColor.r = (Uint8)(dstColor.r * (1 - a));
            dstColor.g = (Uint8)(dstColor.g * (1 - a));
            dstColor.b = (Uint8)(dstColor.b * (1 - a));

            SDL_Color color;
            color.r = srcColor.r + dstColor.r;
            color.g = srcColor.g + dstColor.g;
            color.b = srcColor.b + dstColor.b;
            color.a = 255;

            m_buffer[sx + (sy * m_width)] = ColorToPixel(color);
        }
    }
}




bool Load(const std::string& filename, int alpha = 255);