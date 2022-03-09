//#include "array.h"
#include "array_v2.h"

enum mode {INT, CHAR};

void tester(const Creator& creator, mode m){
    int n = 10;
    int* array1;
    char* array2;
    switch(m){
        case INT:  array1 = (int*) creator.create(n);
                   array1[2] = 457; cout << array1[2] << "\n";
                   break;
        case CHAR: array2 = (char*) creator.create(n);
                   array2[5] = 'H'; cout << array2[5] << "\n";
                   break;
    }
}

int main(void){
    int n = 10;
    /*
    int* array = create(n);
    int* array2;
    array[3] = 145;
    cout << array[3] << "\n";
    insert(array, 3, 225);
    cout << array[3] << "\n";
    eliminate(array);
    cout << array[3] << "\n";
    array = create(n);
    for(int i = 0; i < n; i++)
        array[i] = i;
    cout << search(array, n, 5) << " - " << search(array, n, 45) << "\n";
    array[7] = 3;
    cout << count(array, n, 3) << "\n";
    array2 = create_copy(array, n);
    cout << count(array2, n, 3) << "\n";
    array = reverse(array, n);
    cout << array[0] << " - " << array[1] << " - " << array[2] << "\n";
    */
    intArrayCreator* creator1 = new intArrayCreator();
    tester(*creator1, INT);
    delete creator1;

    charArrayCreator* creator2 = new charArrayCreator();
    tester(*creator2, CHAR);
    delete creator2;

    return 0;
}
