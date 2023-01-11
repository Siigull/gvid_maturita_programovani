    for(int i=0; i<y/2; i++){
        for(int j=0; j<x; j++){
            int temp = pole[j][i];
            pole[j][i] = pole[j][y-i-1];
            pole[j][y-i-1] = temp;
        }
    }