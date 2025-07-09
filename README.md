# heartcoded

This is a sweet Valentine's Day gift project built using inline ARM assembly and C to render hearts and custom messages on a VGA display using the <a href="./DE1-SoC_Computer_ARM.pdf">DE1-SOC Computer Manual</a>.

The program displays dozens of pixelated hearts and two messages on the screen using VGA memory-mapped I/O.

## ❤️ What It Does

- Draws a heart shape using hard-coded pixel offsets
- Fills the VGA screen with a soft background color
- Displays the messages:
  ```
  HAPPY VALENTINE'S DAY!
                  -YOON
  ```
- Renders a 12×9 grid of pixel hearts with animated ASCII placement

## 🛠 Technologies Used

- **Language:** C with Inline ARM Assembly
- **Platform:** DE1-SoC simulator (or actual FPGA board)
- **Display:** VGA Pixel Buffer + Character Buffer

## 🖼️ Preview

![output](./VGA_pixel_buffer_output.jpg)


## 🧠 How It Works

- The pixel buffer (`0xC8000000`) is directly written to via the `VGA_draw_point_ASM` subroutine.
- Characters are displayed through the character buffer (`0xC9000000`) using `VGA_write_char_ASM`.
- Heart shapes are drawn based on a fixed array of relative pixel coordinates.
- Messages are written using ASCII characters at specific (x, y) positions.

## 📂 File Structure

- `hearts.c`: The full program including VGA drawing, message display, and heart rendering logic.

## ▶️ Running the Project

This project is compatible with the **McGill ECSE324 online simulator**:
- Simulator: [https://ecse324.ece.mcgill.ca/simulator/?sys=arm-de1soc](https://ecse324.ece.mcgill.ca/simulator/?sys=arm-de1soc)

To run:
1. Copy-paste `hearts.c` into the simulator.
2. Ensure the language is set to **C**, not ARMv7 assembly.
3. Compile and run — enjoy the animated heart wall!

## 📜 License

This project is a heartfelt gift and is released under the [MIT License](LICENSE).

---

> **Made with ❤️ by Yoon**
