width = 512
height = 512

with open("assets/textures/test.ppm", "wb") as f:
    f.write(b"P6\n")
    f.write(f"{width} {height}\n".encode())
    f.write(b"255\n")

    for y in range(height):
        for x in range(width):
            r = int(255 * x / (width - 1))
            g = int(255 * y / (height - 1))

            if ((x // 32 + y // 32) % 2 == 0):
                b = 180
            else:
                b = 40

            f.write(bytes((r, g, b)))
