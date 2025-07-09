void VGA_draw_point_ASM(int x, int y, short c) {
	__asm__  __volatile__(
        "mov r0, %0\n\t" // Load x into r0
        "mov r1, %1\n\t" // Load y into r1
        "mov r2, %2\n\t" // Load c into r2
        
		"PUSH {R0,R1,R2,R3,R4,LR}\n\t"
        "CMP R0, #0\n\t"
        "BLT break2\n\t"
        "CMP R0, #320\n\t"
        "BGT break2\n\t"
        "CMP R1, #0\n\t"
        "BLT break2\n\t"
        "CMP R1, #240\n\t"
        "BGT break2\n\t"
        "LDR R3, =0xC8000000\n\t" // loading base address
        "LSL R0, R0, #1\n\t"
        "LSL R1, R1, #10\n\t"
        "ORR R4, R0, R1\n\t"
        "ORR R3, R3, R4\n\t"
        "STRH R2, [R3]\n\t"
        "break2:\n\t"
        "POP {R0,R1,R2,R3,R4,LR}\n\t"
        :    
        :"r"(x), "r"(y), "r"(c) // input operands %0, %1, and %2
	);
}

void VGA_clear_pixelbuff_ASM() {
	__asm__  __volatile__(
		"PUSH {R0,R1,R2,LR}\n\t"
        "MOV R0, #0\n\t"
        "MOV R1, #0\n\t"
        "MOV R2, #0\n\t"
        "clearing_loop:\n\t"
        "BL VGA_draw_point_ASM\n\t"
        "ADD R0, #1\n\t"
        "CMP R0, #320\n\t"
        "BLT clearing_loop\n\t"
        "ADD R1, #1\n\t"
        "MOV R0, #0\n\t"
        "CMP R1, #240\n\t"
        "BLT clearing_loop\n\t"
        "POP {R0,R1,R2,LR}\n\t"
	);
}

void VGA_write_char_ASM(int x, int y, char c) {
	__asm__  __volatile__(
		//"mov		r0, %0\n\t"
		//"mov		r1, %1\n\t"
		//"mov		r2, %2\n\t"

		"PUSH {R3, R4, LR}\n\t"
		"CMP R0, #0\n\t"
		"BLT break\n\t"
		"CMP R0, #80\n\t"
		"BGT break\n\t"
		"CMP R1, #0\n\t"
		"BLT break\n\t"
		"CMP R1, #60\n\t"
		"BGT break\n\t"
		"LDR R3, =0xC9000000\n\t" // loading base address
		"LSL R1, R1, #7\n\t"
		"ORR R4, R0, R1\n\t"
		"ORR R3, R3, R4\n\t"
		"STRB R2, [R3]\n\t"
		"break:\n\t"
		"POP {R3, R4, LR}\n\t"
        :    
        :"r"(x), "r"(y), "r"(c) // input operands %0, %1, and %2
	);
}

void VGA_clear_charbuff_ASM() {
	__asm__  __volatile__(
		"PUSH {R0-R4,LR}\n\t"
        "MOV R0, #0\n\t"
        "MOV R1, #0\n\t"
        "MOV R2, #0\n\t"
        "clearing_loop2:\n\t"
        "BL VGA_write_char_ASM\n\t"
        "ADD R0, #1\n\t"
        "CMP R0, #80\n\t"
        "BLT clearing_loop2\n\t"
        "ADD R1, #1\n\t"
        "MOV R0, #0\n\t"
        "CMP R1, #60\n\t"
        "BLT clearing_loop2\n\t"
        "POP {R0-R4,LR}\n\t"
	);
}

int read_PS2_data_ASM(char *data) {
	int val = 0;
	__asm__  __volatile__(
		"mov        r0, %1\n\t"
		
		"PUSH {R1, R2, LR}\n\t"
		"LDR R1, =0xFF200100\n\t"
		"LDR R1, [R1]\n\t"
		"LSR R2, R1, #15\n\t"
		"AND R2, #1\n\t"
		"CMP R2, #1\n\t"
		"STREQB R1, [R0]\n\t"
		"MOVEQ R0, #1\n\t"
		"MOVNE R0, #0\n\t"
		"POP {R1, R2, LR}\n\t"

		"mov        %0, r0\n\t"
		:"=r"(val) // output operands %0
		:"r"(data) // input operands %1
	);
	return val;
}

void VGA_fill_ASM() {
	for (int i = 0; i < 320; i++) {
		for (int j = 0; j < 240; j++) {
			VGA_draw_point_ASM(i, j, 0xdddd);
		}
	}
}


void draw_message1_ASM(int x, int y) {
	VGA_write_char_ASM(x, y, 'H');
	VGA_write_char_ASM(x+1, y, 'A');
	VGA_write_char_ASM(x+2, y, 'P');
	VGA_write_char_ASM(x+3, y, 'P');
	VGA_write_char_ASM(x+4, y, 'Y');
	VGA_write_char_ASM(x+6, y, 'V');
	VGA_write_char_ASM(x+7, y, 'A');
	VGA_write_char_ASM(x+8, y, 'L');
	VGA_write_char_ASM(x+9, y, 'E');
	VGA_write_char_ASM(x+10, y, 'N');
	VGA_write_char_ASM(x+11, y, 'T');
	VGA_write_char_ASM(x+12, y, 'I');
	VGA_write_char_ASM(x+13, y, 'N');
	VGA_write_char_ASM(x+14, y, 'E');
	VGA_write_char_ASM(x+15, y, '\'');
	VGA_write_char_ASM(x+16, y, 'S');
	VGA_write_char_ASM(x+18, y, 'D');
	VGA_write_char_ASM(x+19, y, 'A');
	VGA_write_char_ASM(x+20, y, 'Y');
	VGA_write_char_ASM(x+21, y, '!');
}

void draw_message2_ASM(int x, int y) {
	VGA_write_char_ASM(x, y, '-');
	VGA_write_char_ASM(x+2, y, 'Y');
	VGA_write_char_ASM(x+3, y, 'O');
	VGA_write_char_ASM(x+4, y, 'O');
	VGA_write_char_ASM(x+5, y, 'N');
}

void draw_heart_ASM(int x, int y) {
    // Heart color
    short color = 0xbbbb;

    int topLeftX = x - 6; 
    int topLeftY = y - 7; 
    
    // Hard-coded heart pixel positions relative to top-left corner
    int heartPixels[][2] = {
		{3,0}, {4,0}, {13,0}, {14,0},
		{2,1}, {3,1}, {4,1}, {5,1}, {6,1}, {11,1}, {12,1}, {13,1}, {14,1}, {15,1},
		{1,2}, {2,2}, {3,2}, {4,2}, {5,2}, {6,2}, {7,2}, {10,2}, {11,2}, {12,2}, {13,2}, {14,2}, {15,2}, {16,2},
		{1,3}, {2,3}, {3,3}, {4,3}, {5,3}, {6,3}, {7,3}, {10,3}, {11,3}, {12,3}, {13,3}, {14,3}, {15,3}, {16,3},
		{1,4}, {2,4}, {3,4}, {4,4}, {5,4}, {6,4}, {7,4}, {8,4}, {9,4}, {10,4}, {11,4}, {12,4}, {13,4}, {14,4}, {15,4}, {16,4},
		{1,5}, {2,5}, {3,5}, {4,5}, {5,5}, {6,5}, {7,5}, {8,5}, {9,5}, {10,5}, {11,5}, {12,5}, {13,5}, {14,5}, {15,5}, {16,5},
		{1,6}, {2,6}, {3,6}, {4,6}, {5,6}, {6,6}, {7,6}, {8,6}, {9,6}, {10,6}, {11,6}, {12,6}, {13,6}, {14,6}, {15,6}, {16,6},
		{1,7}, {2,7}, {3,7}, {4,7}, {5,7}, {6,7}, {7,7}, {8,7}, {9,7}, {10,7}, {11,7}, {12,7}, {13,7}, {14,7}, {15,7}, {16,7},
		{1,8}, {2,8}, {3,8}, {4,8}, {5,8}, {6,8}, {7,8}, {8,8}, {9,8}, {10,8}, {11,8}, {12,8}, {13,8}, {14,8}, {15,8}, {16,8},
		{1,9}, {2,9}, {3,9}, {4,9}, {5,9}, {6,9}, {7,9}, {8,9}, {9,9}, {10,9}, {11,9}, {12,9}, {13,9}, {14,9}, {15,9}, {16,9},
		{3,10}, {4,10}, {5,10}, {6,10}, {7,10}, {8,10}, {9,10}, {10,10}, {11,10}, {12,10}, {13,10}, {14,10},
		{3,11}, {4,11}, {5,11}, {6,11}, {7,11}, {8,11}, {9,11}, {10,11}, {11,11}, {12,11}, {13,11}, {14,11},
		{5,12}, {6,12}, {7,12}, {8,12}, {9,12}, {10,12}, {11,12}, {12,12},
		{5,13}, {6,13}, {7,13}, {8,13}, {9,13}, {10,13}, {11,13}, {12,13},
		{7,14}, {8,14}, {9,14}, {10,14},
		{7,15}, {8,15}, {9,15}, {10,15}
	};
    
    // Number of heart pixels defined
    int numHeartPixels = sizeof(heartPixels) / sizeof(heartPixels[0]);

    // Draw each heart pixel at the appropriate position
    for (int i = 0; i < numHeartPixels; i++) {
        int xOffset = topLeftX + heartPixels[i][0];
        int yOffset = topLeftY + heartPixels[i][1];
        VGA_draw_point_ASM(xOffset, yOffset, color);
    }
}

int main() {
	
	VGA_fill_ASM();
	draw_message1_ASM(10, 25);
	draw_message2_ASM(65, 45);
	
	int startX = 13; // Starting X position for hearts
	int startY = 15; // Starting Y position for hearts
	int spacing = 26; // Spacing between hearts
	
	for (int y = 0; y < 9; y++) { // Adjust the number of lines as needed
        int a = startX; // Reset X position to the start for each new line
        for (int x = 0; x < 12; x++) { // Adjust the number of hearts per line as needed
            draw_heart_ASM(a, startY);
            a += spacing; // Move to the next position on the same line
        }
        startY += spacing; // Move to the next line
    }
	
    return 0;
}
