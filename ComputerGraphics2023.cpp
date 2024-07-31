#include <GL/glut.h>
#include <GL/glui.h>
#include <stdio.h>

int main_window;
int Width, Height;
int wire = 0;
int radio;
int num = 1;
int frame = 0;
float change_R, change_G, change_B;
float light_R, light_G, light_B;
GLfloat Light0_Ambient[] = { 0.5, 0.4, 0.3, 1.0 };
GLfloat Light0_Diffuse[] = { 0.9, 0.9, 0.9, 1.0 };
GLfloat Light0_Specular[] = { 0.1, 0.1, 0.1, 1.0 };
GLfloat Light0_Position[] = { 50.0, 50.0, 50.0, 50.0 };
GLfloat Material_Ambient[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat Material_Diffuse[] = { 0.5, 0.5, 0.5, 1.0 };
GLfloat Material_Specular[] = { 0.0, 0.0, 0.0, 1.0 };
GLfloat Material_Shininess[] = { 50.0 };
float rotate[16] = { 1,0, 0,0, 0,1, 0,0, 0,0, 1,0, 0,0, 0,1 };
float trans[3] = { 0.0, 0.0, 0.0 };


struct carinfo {
    int num;                                                    //차량 종류
    float r, g, b;                                              //차량 색상
    int dir;
    int ny, nx, py, px;
};

int matrix[6][6] = {                                            //차량 배치도
    0, 0, 1, 2, 3, 3,
    0, 0, 1, 2, 5, 0,
    8, 8, 1, 2, 5, 0,
    0, 6, 0, 0, 7, 0,
    0, 6, 4, 4, 7, 0,
    0, 0, 0, 0, 0, 0,
};
int resetmatrix[6][6] = {
    0, 0, 1, 2, 3, 3,
    0, 0, 1, 2, 5, 0,
    8, 8, 1, 2, 5, 0,
    0, 6, 0, 0, 7, 0,
    0, 6, 4, 4, 7, 0,
    0, 0, 0, 0, 0, 0, 
};

int matrix1[6][6] = {
            0, 0, 1, 2, 3, 3,
            0, 0, 1, 2, 5, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 0, 0, 0, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix2[6][6] = {
            0, 0, 1, 2, 3, 3,
            0, 0, 1, 2, 0, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 0, 0, 5, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix3[6][6] = {
            0, 0, 0, 2, 3, 3,
            0, 0, 1, 2, 0, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 1, 0, 5, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix4[6][6] = {
            0, 0, 0, 0, 3, 3,
            0, 0, 1, 2, 0, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 1, 2, 5, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix5[6][6] = {
            0, 0, 0, 3, 3, 0,
            0, 0, 1, 2, 0, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 1, 2, 5, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix6[6][6] = {
            0, 0, 3, 3, 0, 0,
            0, 0, 1, 2, 0, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 1, 2, 5, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix7[6][6] = {
           0, 3, 3, 0, 0, 0,
            0, 0, 1, 2, 0, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 1, 2, 5, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix8[6][6] = {
           3, 3, 0, 0, 0, 0,
            0, 0, 1, 2, 0, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 1, 2, 5, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix9[6][6] = {
           3, 3, 0, 0, 0, 0,
            0, 0, 1, 2, 5, 0,
            8, 8, 1, 2, 5, 0,
            0, 6, 1, 2, 0, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix10[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 1, 2, 5, 0,
            8, 8, 1, 2, 0, 0,
            0, 6, 1, 2, 0, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 7, 0,
};
int matrix11[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 1, 2, 5, 0,
            8, 8, 1, 2, 0, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 4, 4, 7, 0,
            0, 0, 0, 0, 0, 0,
};
int matrix12[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 1, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 4, 4, 0, 0,
            0, 0, 0, 0, 0, 0,
};
int matrix13[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 1, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 0, 4, 4, 0,
            0, 0, 0, 0, 0, 0,
};
int matrix14[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 1, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 0, 0, 4, 4,
            0, 0, 0, 0, 0, 0,
};
int matrix15[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 0, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 1, 0, 4, 4,
            0, 0, 0, 0, 0, 0,
};
int matrix16[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 0, 2, 5, 0,
            8, 8, 0, 2, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 1, 0, 4, 4,
            0, 0, 1, 0, 0, 0,
};
int matrix17[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 0, 0, 5, 0,
            8, 8, 0, 2, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 1, 2, 4, 4,
            0, 0, 1, 0, 0, 0,
};
int matrix18[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 0, 0, 5, 0,
            8, 8, 0, 0, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix19[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 0, 0, 5, 0,
            0, 8, 8, 0, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix20[6][6] = {
           3, 3, 0, 0, 5, 0,
            0, 0, 0, 0, 5, 0,
            0, 0, 8, 8, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix21[6][6] = {
           0, 3, 3, 0, 5, 0,
            0, 0, 0, 0, 5, 0,
            0, 0, 8, 8, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix22[6][6] = {
           0, 0, 3, 3, 5, 0,
            0, 0, 0, 0, 5, 0,
            0, 0, 8, 8, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 6, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix23[6][6] = {
           0, 0, 3, 3, 5, 0,
            0, 0, 0, 0, 5, 0,
            0, 6, 8, 8, 7, 0,
            0, 6, 1, 2, 7, 0,
            0, 0, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix24[6][6] = {
           0, 0, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            0, 6, 8, 8, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix25[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            0, 0, 8, 8, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix26[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            0, 8, 8, 0, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix27[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            8, 8, 0, 0, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 1, 2, 4, 4,
            0, 0, 1, 2, 0, 0,
};
int matrix28[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            8, 8, 1, 0, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 1, 2, 4, 4,
            0, 0, 0, 2, 0, 0,
};
int matrix29[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 1, 0, 5, 0,
            8, 8, 1, 0, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 0, 2, 4, 4,
            0, 0, 0, 2, 0, 0,
};
int matrix30[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 1, 0, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 0, 2, 4, 4,
            0, 0, 0, 0, 0, 0,
};
int matrix31[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 1, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 0, 0, 4, 4,
            0, 0, 0, 0, 0, 0,
};
int matrix32[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 1, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 0, 4, 4, 0,
            0, 0, 0, 0, 0, 0,
};
int matrix33[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 1, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 0, 4, 4, 0, 0,
            0, 0, 0, 0, 0, 0,
};
int matrix34[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 1, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            0, 4, 4, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
};
int matrix35[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 1, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            4, 4, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
};
int matrix36[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 2, 5, 0,
            8, 8, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            4, 4, 1, 0, 0, 0,
            0, 0, 0, 0, 0, 0,
};
int matrix37[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 2, 5, 0,
            8, 8, 0, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            4, 4, 1, 0, 0, 0,
            0, 0, 1, 0, 0, 0,
};
int matrix38[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            8, 8, 0, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
            4, 4, 1, 2, 0, 0,
            0, 0, 1, 0, 0, 0,
};
int matrix39[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            8, 8, 0, 0, 7, 0,
            0, 0, 1, 2, 7, 0,
            4, 4, 1, 2, 0, 0,
            0, 0, 1, 2, 0, 0,
};
int matrix40[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            8, 8, 0, 0, 0, 0,
            0, 0, 1, 2, 7, 0,
            4, 4, 1, 2, 7, 0,
            0, 0, 1, 2, 0, 0,
};
int matrix41[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            8, 8, 0, 0, 0, 0,
            0, 0, 1, 2, 0, 0,
            4, 4, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
};
int matrix42[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            0, 8, 8, 0, 0, 0,
            0, 0, 1, 2, 0, 0,
            4, 4, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
};
int matrix43[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            0, 0, 8, 8, 0, 0,
            0, 0, 1, 2, 0, 0,
            4, 4, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
};
int matrix44[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            0, 0, 0, 8, 8, 0,
            0, 0, 1, 2, 0, 0,
            4, 4, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
};
int matrix45[6][6] = {
           0, 6, 3, 3, 5, 0,
            0, 6, 0, 0, 5, 0,
            0, 0, 0, 0, 8, 8,
            0, 0, 1, 2, 0, 0,
            4, 4, 1, 2, 7, 0,
            0, 0, 1, 2, 7, 0,
};

void animate45(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix45[i][j];
        }
    }
}
void animate44(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix44[i][j];
        }
    }
    glutTimerFunc(500, animate45, 1);
}
void animate43(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix43[i][j];
        }
    }
    glutTimerFunc(500, animate44, 1);
}
void animate42(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix42[i][j];
        }
    }
    glutTimerFunc(500, animate43, 1);
}
void animate41(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix41[i][j];
        }
    }
    glutTimerFunc(500, animate42, 1);
}
void animate40(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix40[i][j];
        }
    }
    glutTimerFunc(500, animate41, 1);
}
void animate39(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix39[i][j];
        }
    }
    glutTimerFunc(500, animate40, 1);
}
void animate38(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix38[i][j];
        }
    }
    glutTimerFunc(500, animate39, 1);
}
void animate37(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix37[i][j];
        }
    }
    glutTimerFunc(500, animate38, 1);
}
void animate36(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix36[i][j];
        }
    }
    glutTimerFunc(500, animate37, 1);
}
void animate35(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix35[i][j];
        }
    }
    glutTimerFunc(500, animate36, 1);
}
void animate34(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix34[i][j];
        }
    }
    glutTimerFunc(500, animate35, 1);
}
void animate33(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix33[i][j];
        }
    }
    glutTimerFunc(500, animate34, 1);
}
void animate32(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix32[i][j];
        }
    }
    glutTimerFunc(500, animate33, 1);
}
void animate31(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix31[i][j];
        }
    }
    glutTimerFunc(500, animate32, 1);
}
void animate30(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix30[i][j];
        }
    }
    glutTimerFunc(500, animate31, 1);
}
void animate29(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix29[i][j];
        }
    }
    glutTimerFunc(500, animate30, 1);
}
void animate28(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix28[i][j];
        }
    }
    glutTimerFunc(500, animate29, 1);
}
void animate27(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix27[i][j];
        }
    }
    glutTimerFunc(500, animate28, 1);
}
void animate26(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix26[i][j];
        }
    }
    glutTimerFunc(500, animate27, 1);
}
void animate25(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix25[i][j];
        }
    }
    glutTimerFunc(500, animate26, 1);
}
void animate24(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix24[i][j];
        }
    }
    glutTimerFunc(500, animate25, 1);
}
void animate23(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix23[i][j];
        }
    }
    glutTimerFunc(500, animate24, 1);
}
void animate22(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix22[i][j];
        }
    }
    glutTimerFunc(500, animate23, 1);
}
void animate21(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix21[i][j];
        }
    }
    glutTimerFunc(500, animate22, 1);
}
void animate20(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix20[i][j];
        }
    }
    glutTimerFunc(500, animate21, 1);
}
void animate19(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix19[i][j];
        }
    }
    glutTimerFunc(500, animate20, 1);
}
void animate18(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix18[i][j];
        }
    }
    glutTimerFunc(500, animate19, 1);
}
void animate17(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix17[i][j];
        }
    }
    glutTimerFunc(500, animate18, 1);
}
void animate16(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix16[i][j];
        }
    }
    glutTimerFunc(500, animate17, 1);
}
void animate15(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix15[i][j];
        }
    }
    glutTimerFunc(500, animate16, 1);
}
void animate14(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix14[i][j];
        }
    }
    glutTimerFunc(500, animate15, 1);
}
void animate13(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix13[i][j];
        }
    }
    glutTimerFunc(500, animate14, 1);
}
void animate12(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix12[i][j];
        }
    }
    glutTimerFunc(500, animate13, 1);
}
void animate11(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix11[i][j];
        }
    }
    glutTimerFunc(500, animate12, 1);
}
void animate10(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix10[i][j];
        }
    }
    glutTimerFunc(500, animate11, 1);
}
void animate9(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix9[i][j];
        }
    }
    glutTimerFunc(500, animate10, 1);
}
void animate8(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix8[i][j];
        }
    }
    glutTimerFunc(500, animate9, 1);
}
void animate7(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix7[i][j];
        }
    }
    glutTimerFunc(500, animate8, 1);
}
void animate6(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix6[i][j];
        }
    }
    glutTimerFunc(500, animate7, 1);
}
void animate5(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix5[i][j];
        }
    }
    glutTimerFunc(500, animate6, 1);
}
void animate4(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix4[i][j];
        }
    }
    glutTimerFunc(500, animate5, 1);
}
void animate3(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix3[i][j];
        }
    }
    glutTimerFunc(500, animate4, 1);
}
void animate2(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix2[i][j];
        }
    }
    glutTimerFunc(500, animate3, 1);
}
void animate1(int frame) {
    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 6; j++) {
            matrix[i][j] = matrix1[i][j];
        }
    }
    glutTimerFunc(500, animate2, 1);
}


struct carinfo car[10] = {
    {0, 1, 1, 1, 1, 0, 0, 0, 0},                                //X
    {1, 0, 0, 1, 1, 0, 2, 2, 2},                                //파란색
    {2, 1, 0, 1, 1, 0, 3, 2, 3},                                //보라색
    {3, 0, 1, 1, 2, 0, 4, 0, 5},                                //하늘색
    {4, 0, 1, 0, 2, 4, 2, 4, 3},                                //초록색
    {5, 1, 0, 0, 1, 1, 4, 2, 4},                                //빨간색
    {6, 1, 1, 0, 1, 3, 1, 4, 1},                                //노란색
    {7, 1, 0.5, 0.5, 1, 3, 4, 4, 4},                          //회색
    {8, 1, 0.5, 0, 2, 2, 0, 2, 1},                              //주황색
};

void reshape(int w, int h) {
    Width = w; Height = h;
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-2.0, 2.0, -2.0, 2.0, 0.5, 5.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void DrawCar() {

    //light//
    glLightfv(GL_LIGHT0, GL_AMBIENT, Light0_Ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, Light0_Diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, Light0_Specular);
    glLightfv(GL_LIGHT0, GL_POSITION, Light0_Position);
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, Material_Ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, Material_Diffuse);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, Material_Specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, Material_Shininess);
    glShadeModel(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_COLOR_MATERIAL);
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    glViewport(0, 0, Width, Height);

    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluPerspective(30, 1.0, 3.0, 50.0);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    gluLookAt(17.0, 17.0, 17.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
    glMultMatrixf(rotate);


    //drawground
    
    float x, z;
    glColor3f(0.0, 0.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-6.0, -0.71, 6.0);
    glVertex3f(6.0, -0.71, 6.0);
    glVertex3f(6.0, -0.71, -6.0);
    glVertex3f(-6.0, -0.71, -6.0);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glLineWidth(4.0f);
    for (x = -6.0; x <= 6.0; x += 2.0) {
        glBegin(GL_LINES);
        glVertex3f(x, -0.7, -6.0);
        glVertex3f(x, -0.7, 6.0);
    }
    for (z = -6.0; z <= 6.0; z += 2.0) {
        glVertex3f(-6.0, -0.7, z);
        glVertex3f(6.0, -0.7, z);
    }
    glEnd();
    
    //translate car
    if(car[radio].dir == 1){
        if (trans[1] >= 5) {
            if (car[radio].ny > 0 && matrix[car[radio].ny - 1][car[radio].nx] == 0) {  //차량 위로 이동
                matrix[car[radio].ny - 1][car[radio].nx] = radio;
                matrix[car[radio].py][car[radio].px] = 0;
                car[radio].py--;
                car[radio].ny--;
                trans[1] = 0.0;
            }
            trans[1] = 0.0;
           
        }
    
        else if (trans[1] <= -5) {
            if (car[radio].py < 5 && matrix[car[radio].py + 1][car[radio].px] == 0) {  //차량 아래로 이동
                matrix[car[radio].py + 1][car[radio].px] = radio;
                matrix[car[radio].ny][car[radio].nx] = 0;
                car[radio].py++;
                car[radio].ny++;
                trans[1] = 0.0;
            }
            trans[1] = 0.0;
        }
        trans[1] = 0.0;
    }
    
    if (car[radio].dir == 2) {
        if (trans[0] <= -5) {
            if (car[radio].nx > 0 && matrix[car[radio].ny][car[radio].nx - 1] == 0) {
                matrix[car[radio].ny][car[radio].nx - 1] = radio;
                matrix[car[radio].py][car[radio].px] = 0;
                car[radio].px--;
                car[radio].nx--;
                trans[0] = 0.0;
            }
            trans[0] = 0.0;
        }
        else if (trans[0] >= 5) {
            if (car[radio].px < 5 && matrix[car[radio].py][car[radio].px + 1] == 0) {
                matrix[car[radio].py][car[radio].px + 1] = radio;
                matrix[car[radio].ny][car[radio].nx] = 0;
                car[radio].px++;
                car[radio].nx++;
                trans[0] = 0.0;
            }
            trans[0] = 0.0;
        }
        trans[0] = 0.0;
    }

    //draw car
    for (int z = 0; z < 6; z++) {                                              //자동차 생성
        for (int x = 0; x < 6; x++) {
            num = matrix[z][x];
            if (num != 0) {                                                            //matrix[y][x]의 값이 0인 것은 생성X
                glColor3f(car[num].r, car[num].g, car[num].b);
                glPushMatrix();
                glTranslatef((z - 2.5) * 2, 0.3, (x - 2.5) * -2);
                if (wire == 0) glutSolidCube(2.0);
                else if (wire == 1) glutWireCube(2.0);
                glPopMatrix();
            }
        }
    }
    if (matrix[2][4] == 8 && matrix[2][5] == 8) {
        glTranslatef(-3.0, 4.0, 0.0);
        glColor3f(1.0, 1.0, 1.0); 
        glScalef(0.02, 0.02, 0.02);  

        
        const char* text = "Clear!";
        for (int i = 0; i < strlen(text); ++i) {
            glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);
        }
    }


    glEnd();
    
    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glFlush();
}

void Callback(int id) {
    switch(id){
        case 1: //car select
            GLUI_Master.sync_live_all();
            printf("you selected car%d\n", radio);;
            break;

        case 2: //car color
            car[radio].r = change_R;
            car[radio].g = change_G;
            car[radio].b = change_B;
            printf("you changed car%d color to (%f, %f, %f)\n", radio, change_R, change_G, change_B);
            break;

        case 3: //light color
            Light0_Ambient[0] = light_R;
            Light0_Ambient[1] = light_G;
            Light0_Ambient[2] = light_B;

        case 6: //reset
            for (int i = 0; i < 6; i++) {
                for (int j = 0; j < 6; j++) {
                    matrix[i][j] = resetmatrix[i][j];
                }
            }
            break;

        case 7: //animation
            glutTimerFunc(500, animate1, 1);


    }
}

void myGlutIdle(void) {
    if (glutGetWindow() != main_window) {
        glutSetWindow(main_window);
    }
    glutPostRedisplay();
}

int main(int argc, char* argv[]) {

    ///////////////////////////////////////glut/////////////////////////////////////////
    glutInit(&argc, argv);
    Width = 500; Height = 500;
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(Width, Height);
    main_window = glutCreateWindow("Car Escape 3D play");
    glutDisplayFunc(DrawCar);
    glutReshapeFunc(reshape);




    //glui//
    GLUI* glui = GLUI_Master.create_glui("Menu");

    //Static Text
    GLUI_StaticText* staticText = new GLUI_StaticText(glui, "60181688 Kim Hyeong Jin");

    //Checkbox
    glui->add_checkbox("WireFrame", &wire, 9, Callback);

    //radiobutton & listbox
    GLUI_Panel* panel_car = glui->add_panel("Car_Selection", GLUI_PANEL_EMBOSSED);

    GLUI_RadioGroup* car_option = glui->add_radiogroup_to_panel(panel_car, &radio, 1, Callback);
    GLUI_RadioButton* car0 = glui->add_radiobutton_to_group(car_option, "Car0");
    GLUI_RadioButton* car1 = glui->add_radiobutton_to_group(car_option, "Car1");
    GLUI_RadioButton* car2 = glui->add_radiobutton_to_group(car_option, "Car2");
    GLUI_RadioButton* car3 = glui->add_radiobutton_to_group(car_option, "Car3");
    GLUI_RadioButton* car4 = glui->add_radiobutton_to_group(car_option, "Car4");
    GLUI_RadioButton* car5 = glui->add_radiobutton_to_group(car_option, "Car5");
    GLUI_RadioButton* car6 = glui->add_radiobutton_to_group(car_option, "Car6");
    GLUI_RadioButton* car7 = glui->add_radiobutton_to_group(car_option, "Car7");
    GLUI_RadioButton* car8 = glui->add_radiobutton_to_group(car_option, "Car8");

    GLUI_Listbox* listbox = glui->add_listbox_to_panel(panel_car, "", &radio,  1, Callback);
    listbox->add_item(0, "Car0");
    listbox->add_item(1, "Car1");
    listbox->add_item(2, "Car2");
    listbox->add_item(3, "Car3");
    listbox->add_item(4, "Car4");
    listbox->add_item(5, "Car5");
    listbox->add_item(6, "Car6");
    listbox->add_item(7, "Car7");
    listbox->add_item(8, "Car8");

    //Translation Control
    GLUI_Panel* panel_translation = glui->add_panel("Translation", GLUI_PANEL_EMBOSSED);
    GLUI_Translation* translationControl_X = new GLUI_Translation(panel_translation, "Objects_X", GLUI_TRANSLATION_X, trans);
    translationControl_X->set_speed(0.1);
    GLUI_Translation* translationControl_XY = new GLUI_Translation(panel_translation, "Objects_XY", GLUI_TRANSLATION_XY, trans);
    translationControl_XY->set_speed(0.1);
    glui->add_column_to_panel(panel_translation, false);
    GLUI_Translation* translationControl_Y = new GLUI_Translation(panel_translation, "Objects_Y", GLUI_TRANSLATION_Y, &trans[1]);
    translationControl_Y->set_speed(0.1);
    GLUI_Translation* translationControl_Z = new GLUI_Translation(panel_translation, "Objects_Z", GLUI_TRANSLATION_Z, &trans[2]);
    translationControl_Z->set_speed(0.1);


    //Rotation Control
    GLUI_Panel* panel_rotation = glui->add_panel("Rotation", GLUI_PANEL_EMBOSSED);
    GLUI_Rotation* rotation_control = glui->add_rotation_to_panel(panel_rotation, "View Rot", rotate);


    glui->add_column(true);


    //Car Color
    GLUI_Rollout* Car_Color = glui->add_rollout("Car Color", true);
    GLUI_Panel* panel1 = glui->add_panel_to_panel(Car_Color, "", GLUI_PANEL_NONE);
    GLUI_EditText* Car_R = glui->add_edittext_to_panel(panel1, "R", GLUI_EDITTEXT_FLOAT, &change_R, 2, Callback);
    glui->add_column_to_panel(panel1, false);
    GLUI_Scrollbar* Car_R_Scroll = new GLUI_Scrollbar(panel1, "", GLUI_SCROLL_HORIZONTAL, &change_R, 2, Callback);
    GLUI_Panel* panel2 = glui->add_panel_to_panel(Car_Color, "", GLUI_PANEL_NONE);
    GLUI_EditText* Car_G = glui->add_edittext_to_panel(panel2, "G", GLUI_EDITTEXT_FLOAT, &change_G, 2, Callback);
    glui->add_column_to_panel(panel2, false);
    GLUI_Scrollbar* Car_G_Scroll = new GLUI_Scrollbar(panel2, "", GLUI_SCROLL_HORIZONTAL, &change_G, 2, Callback);
    GLUI_Panel* panel3 = glui->add_panel_to_panel(Car_Color, "", GLUI_PANEL_NONE);
    GLUI_EditText* Car_B = glui->add_edittext_to_panel(panel3, "B", GLUI_EDITTEXT_FLOAT, &change_B, 2, Callback);
    glui->add_column_to_panel(panel3, false);
    GLUI_Scrollbar* Car_B_Scroll = new GLUI_Scrollbar(panel3, "", GLUI_SCROLL_HORIZONTAL, &change_B, 2, Callback);




    //Light Color
    GLUI_Rollout* Light_Color = glui->add_rollout("Light Color", true);
    GLUI_Spinner* R = glui->add_spinner_to_panel(Light_Color, "R", GLUI_SPINNER_FLOAT, &light_R, 3, Callback);
    R->set_int_limits(0, 1.0);  // 값 범위 설정
    GLUI_Spinner* G = glui->add_spinner_to_panel(Light_Color, "G", GLUI_SPINNER_FLOAT, &light_G, 3, Callback);
    G->set_int_limits(0, 1.0);  // 값 범위 설정
    GLUI_Spinner* B = glui->add_spinner_to_panel(Light_Color, "B", GLUI_SPINNER_FLOAT, &light_B, 3, Callback);
    B->set_int_limits(0, 1.0);  // 값 범위 설정
    


    //Button
    GLUI_Button* reset = glui->add_button("reset", 6, Callback);
    GLUI_Button* animation = glui->add_button("animation", 7, Callback);
    glui->add_separator();
    GLUI_Button* Quit = glui->add_button("Quit", 0, (GLUI_Update_CB)exit);

    glui->set_main_gfx_window(main_window);
    GLUI_Master.set_glutIdleFunc(myGlutIdle);
    glutMainLoop();
    return 0;
}
