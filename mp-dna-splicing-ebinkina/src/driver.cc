#include "dna_strand.hpp"

int main() {
    
    DNAstrand my_linked_list;

    std::cout << "---------\n";  //   cbababa[ba] => cbababa[uvwxyz]
    std::string s("cbabababa");
    for(char c : s) {
        my_linked_list.PushBack(c);
    }
    my_linked_list.Print("ORIGINAL:");


    DNAstrand splice_in_1;
    std::string replacement = "uvwxyz";
    for(char c : replacement){
        splice_in_1.PushBack(c);
    }
    splice_in_1.Print("REPLACEMENT:");
    my_linked_list.SpliceIn("ba", splice_in_1 );
    my_linked_list.Print("ORIGINAL AFTER REPLACEMENT:");
    splice_in_1.Print("REPLACEMENT AFTER SPLICING:");
    std::cout << "---------\n";
    std::cout << "final count=" << Node::count << '\n';

//-----------------------------------------------------------------------
    replacement = "top";     //   [c]bababauvwxyz -> [top]bababauvwxyz
    for(char c : replacement){
        splice_in_1.PushBack(c);
    }
    splice_in_1.Print("REPLACEMENT:");
    my_linked_list.SpliceIn("c", splice_in_1 );
    my_linked_list.Print("ORIGINAL AFTER REPLACEMENT:");
    splice_in_1.Print("REPLACEMENT AFTER SPLICING:");
    std::cout << "---------\n";
    std::cout << "final count=" << Node::count << '\n';

//-----------------------------------------------------------------------
    replacement = "mno";     //   topbababa[u]vwxyz-> topbababa[mno]vwxyz
    for(char c : replacement){
        splice_in_1.PushBack(c);
    }
    splice_in_1.Print("REPLACEMENT:");
    my_linked_list.SpliceIn("u", splice_in_1 );
    my_linked_list.Print("ORIGINAL AFTER REPLACEMENT:");
    splice_in_1.Print("REPLACEMENT AFTER SPLICING:");
    std::cout << "---------\n";
    std::cout << "final count=" << Node::count << '\n'; 

//-----------------------------------------------------------------------
    replacement = "c";     //   [topbaba]bamnovwxyz-> [c]bamnovwxyz
    for(char c : replacement){
        splice_in_1.PushBack(c);
    }
    splice_in_1.Print("REPLACEMENT:");
    my_linked_list.SpliceIn("topbaba", splice_in_1 );
    my_linked_list.Print("ORIGINAL AFTER REPLACEMENT:");
    splice_in_1.Print("REPLACEMENT AFTER SPLICING:");
    std::cout << "---------\n";
    std::cout << "final count=" << Node::count << '\n';

//-----------------------------------------------------------------------
    replacement = "w";     //   cbamno[vwxyz] -> cbamno[w]
    for(char c : replacement){
        splice_in_1.PushBack(c);
    }
    splice_in_1.Print("REPLACEMENT:");
    my_linked_list.SpliceIn("vwxyz", splice_in_1 );
    my_linked_list.Print("ORIGINAL AFTER REPLACEMENT:");
    splice_in_1.Print("REPLACEMENT AFTER SPLICING:");
    std::cout << "---------\n";
    std::cout << "final count=" << Node::count << '\n';

//-----------------------------------------------------------------------
    replacement = "k";     //   cb[amno]w -> cb[k]w
    for(char c : replacement){
        splice_in_1.PushBack(c);
    }
    splice_in_1.Print("REPLACEMENT:");
    my_linked_list.SpliceIn("amno", splice_in_1 );
    my_linked_list.Print("ORIGINAL AFTER REPLACEMENT:");
    splice_in_1.Print("REPLACEMENT AFTER SPLICING:");
    std::cout << "---------\n";
    std::cout << "final count=" << Node::count << '\n';

    return 0;
}