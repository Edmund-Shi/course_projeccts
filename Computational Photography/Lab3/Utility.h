//
// Created by 36202 on 03/04/2017.
//

#ifndef LAB3_UTILITY_H
#define LAB3_UTILITY_H


class Utility {
    public:
    static void ArrayCopy(double *dst,double * src,double len){
        for (int i = 0; i < len; ++i) {
            dst[i] = src[i];
        }
    }

    // 如果两个数组相同，那么返回值是0，否则返回值是1
    static double ArrayCmp(double *dst,double *src,double len){
        for (int i = 0; i < len; ++i) {
            if(dst[i] != src[i]){
                return 1;
            }
        }
        return 0;
    }
};


#endif //LAB3_UTILITY_H
