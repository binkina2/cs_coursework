// clang-format off
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
//  Written By : Student Name                    Environment : ubuntu:bionic               //
//  Date ......: 2021/02/10                      Compiler ...: clang-10                    //
/////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////
// clang-format on
/////////////////////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up //
/////////////////////////////////////////////////////////////////////////////////////////////
#include "catch.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

#include "CharPositions.hpp"
#include "WordLocation.hpp"
#include "WordSearchSolver.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                             Helpers/Constants //
/////////////////////////////////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////////////////////////////
//                                Test Cases //
/////////////////////////////////////////////////////////////////////////////////////////////

TEST_CASE("True == True", "") { REQUIRE(true == true); }

/////////////////////////////////////////////////////////////////////////////////////////////

/// ** HORIZONTAL TESTS ****

//horizontal 

TEST_CASE("Find horizontal winner 1" , "[found horizatal word hello]") {

    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'h', 'e', 'l', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='h', .row=1, .col=0}, 
        {.character='e', .row=1, .col=1},
        {.character='l', .row=1, .col=2},
        {.character='l', .row=1, .col=3},
        {.character='l', .row=1, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("hello", CheckDirection::kHorizontal);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word == "hello");

    bool matches = true;
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        if ( w.char_positions[i].character != expected_char_positions[i].character && 
             w.char_positions[i].row != expected_char_positions[i].row &&
             w.char_positions[i].col != expected_char_positions[i].col) {
            
            matches = false;
        }
    }
    REQUIRE(matches == true);

}

TEST_CASE("Find horizontal winner 4" , "[found horizatal word bat]") {
    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                        {'b', 'a', 't', 'l', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'e', 't', 'a', 'u'},
                                        {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='b', .row=1, .col=0}, 
        {.character='a', .row=1, .col=1},
        {.character='t', .row=1, .col=2},
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("bat", CheckDirection::kHorizontal);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word == "bat");

    bool matches = true;
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        if ( w.char_positions[i].character != expected_char_positions[i].character && 
             w.char_positions[i].row != expected_char_positions[i].row &&
             w.char_positions[i].col != expected_char_positions[i].col) {
            
            matches = false;
        }
    }
    REQUIRE(matches == true);
}

TEST_CASE("Find horizontal winner 2" , "[not found horizatal word Liza]") {

    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                         {'h', 'e', 'l', 'l', 'o'},
                                         {'c', 'a', 'l', 'o', 'm'},
                                         {'a', 'e', 't', 'a', 'u'},
                                         {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "Liza";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='h', .row=1, .col=0}, 
        {.character='e', .row=1, .col=1},
        {.character='l', .row=1, .col=2},
        {.character='l', .row=1, .col=3},
        {.character='l', .row=1, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("Liza", CheckDirection::kHorizontal);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);

}

TEST_CASE("Find horizontal winner 3", "[not found horizontol word bat]") {
     // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                         {'b', 'a', 'a', 't', 'o'},
                                         {'c', 'a', 'l', 'o', 'm'},
                                         {'a', 'e', 't', 'a', 'u'},
                                         {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "bat";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='b', .row=1, .col=0}, 
        {.character='a', .row=1, .col=1},
        {.character='t', .row=1, .col=2},
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("Liza", CheckDirection::kHorizontal);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);
}


//vertical

TEST_CASE("Find vertical winner 1" , "[found vertical word hello]") {

   std::vector<std::vector<char>> puzzle{{'d', 'h', 'a', 'o', 'u'},
                                         {'w', 'e', 'q', 'u', 'o'},
                                         {'c', 'l', 'l', 'o', 'm'},
                                         {'a', 'l', 't', 'a', 'u'},
                                         {'t', 'o', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='h', .row=0, .col=1}, 
        {.character='e', .row=1, .col=1},
        {.character='l', .row=2, .col=1},
        {.character='l', .row=3, .col=1},
        {.character='l', .row=4, .col=1}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("hello", CheckDirection::kVertical);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word == "hello");

    bool matches = true;
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        if ( w.char_positions[i].character != expected_char_positions[i].character && 
             w.char_positions[i].row != expected_char_positions[i].row &&
             w.char_positions[i].col != expected_char_positions[i].col) {
            
            matches = false;
        }
    }
    REQUIRE(matches == true);

}

TEST_CASE("Find vertical winner 4" , "[found vertical word bat]") {

   std::vector<std::vector<char>> puzzle{{'d', 'b', 'a', 'o', 'u'},
                                         {'w', 'a', 'q', 'u', 'o'},
                                         {'c', 't', 'l', 'o', 'm'},
                                         {'a', 'l', 't', 'a', 'u'},
                                         {'t', 'o', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "bat";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='b', .row=0, .col=1}, 
        {.character='a', .row=1, .col=1},
        {.character='t', .row=2, .col=1},
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("bat", CheckDirection::kVertical);
    
    // Step 4: compare actual result against expected result


    bool matches = true;
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        if ( w.char_positions[i].character != expected_char_positions[i].character && 
             w.char_positions[i].row != expected_char_positions[i].row &&
             w.char_positions[i].col != expected_char_positions[i].col) {
            
            matches = false;
        }
    }
    REQUIRE(matches == true);

}


TEST_CASE("Find vertical winner 2" , "[not found vertical word hello]") {
   // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'d', 'h', 'a', 'o', 'u'},
                                         {'h', 'e', 'l', 'l', 'o'},
                                         {'c', 'a', 'l', 'o', 'm'},
                                         {'a', 'l', 't', 'a', 'u'},
                                         {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='h', .row=1, .col=0}, 
        {.character='e', .row=1, .col=1},
        {.character='l', .row=1, .col=2},
        {.character='l', .row=1, .col=3},
        {.character='l', .row=1, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("hello", CheckDirection::kVertical);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);

}

TEST_CASE("Find vertical winner 3" , "[not found vertical word bat]") {
   // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'d', 'b', 'a', 'o', 'u'},
                                         {'h', 'e', 'l', 'l', 'o'},
                                         {'c', 't', 'l', 'o', 'm'},
                                         {'a', 'l', 't', 'a', 'u'},
                                         {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='b', .row=1, .col=0}, 
        {.character='a', .row=1, .col=1},
        {.character='t', .row=1, .col=2},
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("bat", CheckDirection::kVertical);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);

}


//left diag 

TEST_CASE("Find left diag winner 1", "[found left diag winner]") {
     // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'h', 'e', 'a', 'o', 'h'},
                                        {'h', 'h', 'l', 'e', 'o'},
                                        {'c', 'a', 'l', 'o', 'm'},
                                        {'a', 'l', 't', 'q', 'u'},
                                        {'o', 'e', 't', 'o', 'p'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='h', .row=0, .col=4}, 
        {.character='e', .row=1, .col=3},
        {.character='l', .row=2, .col=2},
        {.character='l', .row=3, .col=1},
        {.character='l', .row=4, .col=0}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("hello", CheckDirection::kLeftDiag);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word == "hello");

    bool matches = true;
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        if ( w.char_positions[i].character != expected_char_positions[i].character && 
             w.char_positions[i].row != expected_char_positions[i].row &&
             w.char_positions[i].col != expected_char_positions[i].col) {
            
            matches = false;
        }
    }
    REQUIRE(matches == true);
}

TEST_CASE("Find left diag winner 3", "[found left diag winner bat]") {
     // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'w', 'e', 'a', 'o', 'h'},
                                        {'h', 'q', 'l', 'b', 'o'},
                                        {'c', 'a', 'a', 'o', 'm'},
                                        {'a', 't', 't', 't', 'u'},
                                        {'o', 'e', 't', 'o', 'p'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='b', .row=1, .col=3},
        {.character='a', .row=2, .col=2},
        {.character='t', .row=3, .col=1},
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("bat", CheckDirection::kLeftDiag);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word == "bat");

    bool matches = true;
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        if ( w.char_positions[i].character != expected_char_positions[i].character && 
             w.char_positions[i].row != expected_char_positions[i].row &&
             w.char_positions[i].col != expected_char_positions[i].col) {
            
            matches = false;
        }
    }
    REQUIRE(matches == true);
}

TEST_CASE("Find left diag winner 2", "[not found left diag winner]") {
    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'d', 'e', 'a', 'o', 'u'},
                                         {'h', 'e', 'l', 'l', 'o'},
                                         {'c', 'a', 'l', 'o', 'm'},
                                         {'a', 'e', 't', 'a', 'u'},
                                         {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='h', .row=0, .col=4}, 
        {.character='e', .row=1, .col=3},
        {.character='l', .row=2, .col=2},
        {.character='l', .row=3, .col=1},
        {.character='l', .row=4, .col=0}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("hello", CheckDirection::kLeftDiag);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);
}

TEST_CASE("Find left diag winner 4", "[not found left diag winner bat]") {
    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'w', 'e', 'a', 'o', 'h'},
                                        {'h', 'q', 'l', 'b', 'o'},
                                        {'c', 'a', 'a', 'o', 'm'},
                                        {'a', 'a', 't', 't', 'u'},
                                        {'o', 'e', 't', 'o', 'p'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='b', .row=1, .col=3},
        {.character='a', .row=2, .col=2},
        {.character='t', .row=3, .col=1},
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("bat", CheckDirection::kLeftDiag);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);
}


//right diag 

TEST_CASE("Find right diag winner 1", "[found right diag winner]") {
     // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'r', 'e', 'a', 'o', 'h'},
                                        {'h', 'o', 'l', 'e', 'o'},
                                        {'c', 'a', 'b', 'o', 'm'},
                                        {'a', 'l', 't', 'o', 'u'},
                                        {'o', 'e', 't', 'o', 't'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "hello";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='r', .row=0, .col=0}, 
        {.character='o', .row=1, .col=1},
        {.character='b', .row=2, .col=2},
        {.character='o', .row=3, .col=3},
        {.character='t', .row=4, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("robot", CheckDirection::kRightDiag);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word == "robot");

    bool matches = true;
    for (size_t i = 0; i < w.char_positions.size(); ++i) {
        if ( w.char_positions[i].character != expected_char_positions[i].character && 
             w.char_positions[i].row != expected_char_positions[i].row &&
             w.char_positions[i].col != expected_char_positions[i].col) {
            
            matches = false;
        }
    }
    REQUIRE(matches == true);
}

TEST_CASE("Find right diag winner 2" , "[not found right diag winner ]") {
    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'q', 'e', 'a', 'o', 'u'},
                                         {'h', 'o', 'l', 'l', 'o'},
                                         {'c', 'a', 'l', 'o', 'm'},
                                         {'a', 'e', 't', 'o', 'u'},
                                         {'t', 'e', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "robot";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='r', .row=0, .col=0}, 
        {.character='o', .row=1, .col=1},
        {.character='b', .row=2, .col=2},
        {.character='o', .row=3, .col=3},
        {.character='t', .row=4, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("robot", CheckDirection::kRightDiag);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);
}

TEST_CASE("Find right diag winner 3" , "[not found right diag winner ]") {
    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'r', 'r', 'a', 'o', 'u'},
                                         {'o', 'o', 'l', 'l', 'o'},
                                         {'b', 'b', 'l', 'o', 'm'},
                                         {'o', 'o', 't', 'o', 'u'},
                                         {'t', 't', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "robot";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='r', .row=0, .col=0}, 
        {.character='o', .row=1, .col=1},
        {.character='b', .row=2, .col=2},
        {.character='o', .row=3, .col=3},
        {.character='t', .row=4, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("robot", CheckDirection::kRightDiag);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);
}

TEST_CASE("Find right diag winner 4" , "[not found right diag winner bat ]") {
    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{'w', 'r', 'a', 'o', 'u'},
                                         {'o', 'b', 'l', 'l', 'o'},
                                         {'b', 'b', 't', 'o', 'm'},
                                         {'o', 'o', 't', 't', 'u'},
                                         {'t', 't', 't', 'o', 'u'}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "robot";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character='b', .row=1, .col=1},
        {.character='a', .row=3, .col=3},
        {.character='t', .row=4, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("bat", CheckDirection::kRightDiag);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);
}

//if empty

TEST_CASE("Check if word search is empty" , "[word search is actually empty]") {

    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{' ', ' ', ' ', ' ', ' '},
                                        {' ', ' ', ' ', ' ', ' '},
                                        {' ', ' ', ' ', ' ', ' '},
                                        {' ', ' ', ' ', ' ', ' '},
                                        {' ', ' ', ' ', ' ', ' '}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character=' ', .row=1, .col=0}, 
        {.character=' ', .row=1, .col=1},
        {.character=' ', .row=1, .col=2},
        {.character=' ', .row=1, .col=3},
        {.character=' ', .row=1, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("", CheckDirection::kHorizontal);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word == "");

}

TEST_CASE("Check if word search is empty 2" , "[word search is not actually empty]") {
    // Step 1: populate puzzle
   std::vector<std::vector<char>> puzzle{{' ', ' ', ' ', ' ', ' '},
                                        {' ', 'a', ' ', ' ', ' '},
                                        {' ', ' ', ' ', ' ', ' '},
                                        {' ', ' ', ' ', ' ', ' '},
                                        {' ', ' ', ' ', ' ', ' '}};
    WordSearchSolver myPuzzle(puzzle);

    // Step 2: create expected values
    std::string expected_word = "";
    std::vector<CharPositions>  expected_char_positions = { 
        {.character=' ', .row=1, .col=0}, 
        {.character=' ', .row=1, .col=1},
        {.character=' ', .row=2, .col=2},
        {.character=' ', .row=1, .col=3},
        {.character=' ', .row=1, .col=4}
         };

    // Step 3: generate results of tested function
    WordLocation w = myPuzzle.FindWord("", CheckDirection::kHorizontal);
    
    // Step 4: compare actual result against expected result

    REQUIRE(w.word.empty() == true);
    REQUIRE(w.char_positions.empty() == true);

}
    
