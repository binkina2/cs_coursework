#include <iostream>
#include "elevation_dataset.hpp"
#include "grayscale_image.hpp"
#include "path_image.hpp"

using namespace std;

int main() {

    int height = 5;
    int width = 6;

    ElevationDataset e("a.txt", width, height);

    cout << "max=" << e.MaxEle() << ' ' << "min=" << e.MinEle() << '\n' << endl;

    for(size_t i=0; i < e.Height(); ++i) { // col
        for(size_t j =0; j < e.Width(); ++j) { // row
            cout << e.DatumAt(i, j) <<  " ";
        }
        cout << endl;
    }

    GrayscaleImage g(e);
    g.ToPpm( "b.txt" );
    
    PathImage p(g, e);
    p.ToPpm("c.txt");

}