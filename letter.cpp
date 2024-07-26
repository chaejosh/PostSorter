// Project Identifier: 50EB44D3F029ED934858FFFCEAC3547C68768FC9
#include <iostream>
#include <string.h>
#include <getopt.h>
#include <vector>
#include <deque>


using namespace std;
class lettermanClass{
    private:
    struct Dictionary{
        Dictionary(){};
        string word = "nothing";
        size_t prev = 100;
        bool found = false;
    };
    vector<Dictionary> dictVect;
    vector<size_t> indexVect; //vector of indeces of change
    vector<char> morphVect; //vector of morphs implemeneted
    vector<char> lettVect; //vector of letters changed
    string beginWord = "beginNothing";
    string endWord = "endNothing";
    string dictType = "R"; //type of dict S or C
    size_t size = 1; //size of dict
    bool stackMode = true; //stack = true, queue = false
    int outFormat; //0 = word, 1 = modification
    bool change = false; //is change command
    bool len = false; //is len command
    bool swap = false; //is swap command
    size_t beginWordIndex = 100; //index of beginWord in dictionary
    size_t endWordIndex = 100; //index of endWord in dictionary
    size_t currentWord = 100; //index of current word in dictionary
    bool endNotFoundPrint = false;
    size_t morphCount = 0;
    int totalCount = 0;
    size_t dictSize = 0;
    public:
    
    //HELPER functions
    void printHelp(){
        cout << "This program starts with one word and converts it to another using a dictionary of similar words!\n";
        cout << "-q: uses a search container that behaves like a queue\n";
        cout << "-s: uses a search container that behaves like a stack\n";
        cout << "-b: specifies the word that Letterman starts with\n";
        cout << "-e: specifies the word that Letterman must reach\n";
        cout << "-o: specfies ouput format\n";
        cout << "-c: allows Letterman to change one letter into another during morphs\n";
        cout << "-l: allows Letterman to insert or delete a single letter during morphs\n";
        cout << "-p: allows Letterman to swap any two adjacent letters during morphs\n";
    }
    
    void backTrace(){
        size_t endDup = endWordIndex;
        while(endDup != beginWordIndex){
            bool morphed = false;
            totalCount++;
            if(change){
                morphed = changeFunc(endDup,true); //go into functions and alter vectors
            }
            if(!morphed && len){
                morphed = remove(endDup, true);
                if(!morphed){
                    morphed = add(endDup, true);
                }
            }
            if(!morphed && swap){
                morphed = swapFunc(endDup, true);
            }
            endDup = dictVect[endDup].prev; //??
        }
    }
    bool changeFunc(size_t index, bool backing){
        int differences = 0;
        if(backing){
        size_t dummint = 0;
            if(dictVect[index].word.size() == dictVect[dictVect[index].prev].word.size()){
                for(size_t j = 0; j < dictVect[dictVect[index].prev].word.size(); j++){
                    if(dictVect[index].word[j] != dictVect[dictVect[index].prev].word[j]){
                        differences++;
                        dummint = j;
                    }
                }
                if(differences == 1){
                    lettVect.push_back(dictVect[index].word[dummint]);
                    indexVect.push_back(dummint);
                    morphVect.push_back('c');
                    morphCount++;
                    
                    return true; 
                }
            }
            return false;
        }
        else{
            if(dictVect[index].word.size() == dictVect[currentWord].word.size()){
                for(size_t j = 0; j < dictVect[currentWord].word.size(); j++){
                    if(dictVect[index].word[j] != dictVect[currentWord].word[j]){
                        differences++;
                    }
                }
                if(differences == 1){
                    dictVect[index].found = true;
                    dictVect[index].prev = currentWord;
                    return true;
                }
            
            }
                return false;
        }
        
    }
    bool swapFunc(size_t index, bool backing){
        
        if(backing){
            if(dictVect[index].word.size() == dictVect[dictVect[index].prev].word.size()){
            for(size_t j = 0; j < dictVect[dictVect[index].prev].word.size() - 1; j++){ //apple, paple, apple, aplpe, appel, swap 4 times 
                string copyer = dictVect[index].word; //copy to swap
                char temp = copyer[j];
                copyer[j] = copyer[j+1];
                copyer[j+1] = temp;
                if(copyer == dictVect[dictVect[index].prev].word){
                    //lettVect.push_back(dictVect[index].word[j]);
                    indexVect.push_back(j);
                    morphVect.push_back('s');
                    morphCount++;
                    return true;
                }
            }
            }
            return false;
        }
        else{
            if(dictVect[index].word.size() == dictVect[currentWord].word.size()){
            //swaps adjacent pairs and checks with currentWord
            for(size_t j = 0; j < dictVect[currentWord].word.size() - 1; j++){ //apple, paple, apple, aplpe, appel, swap 4 times 
                string copyer = dictVect[index].word; //copy to swap
                char temp = copyer[j];
                copyer[j] = copyer[j+1];
                copyer[j+1] = temp;
                if(copyer == dictVect[currentWord].word){
                    dictVect[index].found = true;
                    //lettVect.push_back(dictVect[index].word[j]);
                    dictVect[index].prev = currentWord;
                    return true;
                }
            }
            }
            return false;
        }
        
    }
    bool add(size_t index, bool backing){
        if(backing){
            size_t tempLol = dictVect[dictVect[index].prev].word.size();
            if(tempLol+1 == dictVect[index].word.size()){//can add one letter
            if(dictVect[dictVect[index].prev].word[0] != dictVect[index].word[0]){// check when first letters are same
                if(dictVect[dictVect[index].prev].word == dictVect[index].word.substr(1)){
                    lettVect.push_back(dictVect[index].word[0]);
                    indexVect.push_back(0);
                    morphVect.push_back('i');
                    morphCount++;
                    return true;
                }
                return false;
            }
            for(size_t j = 0; j < tempLol; j++){
                if(dictVect[dictVect[index].prev].word[j] != dictVect[index].word[j]){
                    if(dictVect[dictVect[index].prev].word.substr(j) == dictVect[index].word.substr(j+1)){
                        lettVect.push_back(dictVect[index].word[j]);
                        indexVect.push_back(j);
                        morphVect.push_back('i');
                        morphCount++;
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
             //if additional letter is at the end
                lettVect.push_back(dictVect[index].word[dictVect[index].word.size()-1]);
                indexVect.push_back(dictVect[index].word.size()-1);
                morphVect.push_back('i');
                morphCount++;
                return true;
        }
        }//BACKING^^^^^^ _______--------------------------------------------------
        else{
            if(dictVect[currentWord].word.size()+1 == dictVect[index].word.size()){//can add one letter
            if(dictVect[currentWord].word[0] != dictVect[index].word[0]){// check when first letters are same
                if(dictVect[currentWord].word == dictVect[index].word.substr(1)){
                    dictVect[index].found = true;
                    dictVect[index].prev = currentWord;
                    return true;
                }
                return false;
            }
            for(size_t j = 0; j < dictVect[currentWord].word.size(); j++){
                if(dictVect[currentWord].word[j] != dictVect[index].word[j]){
                    //currentword is shorter than index.word
                    if(dictVect[currentWord].word.substr(j) == dictVect[index].word.substr(j+1)){
                        dictVect[index].found = true;
                        dictVect[index].prev = currentWord;
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
             //if additional letter is at the end
                dictVect[index].found = true;
                dictVect[index].prev = currentWord;
                return true;
        }
        }
        
        return false;
    }
    
    bool remove(size_t index, bool backing){
        if(backing){
            if(dictVect[dictVect[index].prev].word.size()-1 == dictVect[index].word.size()){//can remove one letter
            if(dictVect[dictVect[index].prev].word[0] != dictVect[index].word[0]){// check when first letters are same
                if(dictVect[dictVect[index].prev].word.substr(1) == dictVect[index].word){
                    indexVect.push_back(0);
                    morphVect.push_back('d');
                    morphCount++;
                    return true;
                }
                return false;
            }
            for(size_t j = 0; j < dictVect[index].word.size(); j++){
                if(dictVect[dictVect[index].prev].word[j] != dictVect[index].word[j]){
                    if(dictVect[dictVect[index].prev].word.substr(j+1) == dictVect[index].word.substr(j)){
                        indexVect.push_back(j);
                        morphVect.push_back('d');
                        morphCount++;
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
                indexVect.push_back(dictVect[dictVect[index].prev].word.size()-1);
                morphVect.push_back('d');
                morphCount++;
                
                return true;
            
        }
        } // BACKING ----------------^^^^^^^^^^^^^^^^^^^^^
        else{
            if(dictVect[currentWord].word.size()-1 == dictVect[index].word.size()){//can remove one letter
            if(dictVect[currentWord].word[0] != dictVect[index].word[0]){// check when first letters are same
                if(dictVect[currentWord].word.substr(1) == dictVect[index].word){
                    dictVect[index].found = true;
                    
                    dictVect[index].prev = currentWord;
                    return true;
                }
                return false;
            }
            for(size_t j = 0; j < dictVect[index].word.size(); j++){
                if(dictVect[currentWord].word[j] != dictVect[index].word[j]){
                    if(dictVect[currentWord].word.substr(j+1) == dictVect[index].word.substr(j)){
                        dictVect[index].found = true;
                        
                        dictVect[index].prev = currentWord;
                        return true;
                    }
                    else{
                        return false;
                    }
                }
            }
                
                dictVect[index].found = true;
                dictVect[index].prev = currentWord;
                return true;
            
        }
        }
        
        return false;
    }


    //-----------
    void getOpt(int argc, char * argv[]){
        int gotopt;
        int option_index = 0;
        option long_opts[] = {
            {"help", no_argument, nullptr, 'h'},
            {"queue", no_argument, nullptr, 'q'},
            {"stack", no_argument, nullptr, 's'},
            {"begin", required_argument, nullptr, 'b'},
            {"end", required_argument, nullptr, 'e'},
            {"output", required_argument, nullptr, 'o'},
            {"change", no_argument, nullptr, 'c'},
            {"length", no_argument, nullptr, 'l'},
            {"swap", no_argument, nullptr, 'p'},
            {nullptr, 0, nullptr, '\0'}
        };
        int sqCount = 0;
        bool cPresent = false;
        bool lPresent = false;
        bool pPresent = false;
        bool oArgPresent = false;
        while((gotopt = getopt_long(argc, argv, "hqsb:e:o:clp", long_opts, &option_index)) != -1){
            switch(gotopt){
                case 'h':{
                    printHelp();
                    exit(1);
                }
                case 'q': {
                    sqCount++;
                    stackMode = false;
                    break;
                }
                case 's':{
                    sqCount++;
                    stackMode = true;
                    break;
                }
                case 'b':{
                    string arg(optarg);
                    beginWord = arg;
                    break;
                }
                
                case 'e':{
                    string arg(optarg);
                    endWord = arg;
                    break;
                }
                
                case 'o':{
                     string arg(optarg);
                    //if(arg != "W" && arg != "M"){
                    //    cerr << "Error: Invalid output mode specified\n";
                    //    exit(1);
                    //}
                    if(arg == "W"){
                        outFormat = 0;
                        oArgPresent = true;
                    }
                    else if(arg == "M"){
                        outFormat = 1;
                        oArgPresent = true;
                    }
                    else if(arg!="W" && arg!= "M"){
                        cerr << "Error: Invalid output mode specified\n";
                        exit(1);
                    }
                    break;
                }
                case 'c':{
                    cPresent = true;
                    change = true;
                    break;
                }
                case 'l':{
                    lPresent = true;
                    len = true;
                    break;
                }
                case 'p':{
                    pPresent = true;
                    swap = true;
                    break;
                }
                default:{
                    cerr << "Unknown command line option\n";
                    exit(1);
                }
            }
        }
        if(sqCount > 1){
            cerr << "Error: Conflicting or duplicate stack and queue specified\n";
            exit(1);
        } 
        else if(sqCount == 0){
            cerr << "Error: Must specify one of stack or queue\n";
            exit(1);
        }
        if(!cPresent && !lPresent && !pPresent){
            cerr << "Error: Must specify at least one modification mode (change length swap)\n";
            exit(1);
        }
        
        if(cPresent && pPresent && !lPresent && beginWord.size() != endWord.size()){
            cerr << "Error: The first and last words must have the same length when length mode is off\n";
            exit(1);
        }
        if(!oArgPresent){
            outFormat = 0;
        }

    }

    void read(){
        //add words to dictVect vector?
        cin >> dictType;
        cin >> size;
        dictVect.reserve(size);
        //lettVect.reserve(size);
        //morphVect.reserve(size);
        //indexVect.reserve(size);
        string junkCheck;
        cin >> junkCheck;
        while(junkCheck.find("//") !=std::string::npos){
            getline(cin, junkCheck);
            cin >> junkCheck;
        }
        //junkCheck is now the first word in dictionary
        if(dictType == "S"){
            for(size_t n = 0; n < size; n++){
                Dictionary dic;
                dic.word = junkCheck;
                if(junkCheck == endWord){ 
                    endWordIndex = dictVect.size();

                }
                else if(junkCheck == beginWord){
                    beginWordIndex = dictVect.size();
                }
                dictVect.push_back(dic);
                cin >> junkCheck;
            }
        }
        else{
            for(size_t n = 0; n < size; n++){
            Dictionary dic;
            bool specialChar = false;
            //check for &
            size_t ampCheck = junkCheck.find("&");
            if(ampCheck !=std::string::npos){
                specialChar = true;
                junkCheck.erase(junkCheck.size()-1); //desserts& --> desserts
                dic.word = junkCheck; //desserts
                if(junkCheck == endWord){ 
                    endWordIndex = dictVect.size();
                }
                else if(junkCheck == beginWord){
                    beginWordIndex = dictVect.size();
                }
                dictVect.push_back(dic);
                string reverse = "";
                size_t l = junkCheck.size()-1;
                for(size_t i = 0; i < junkCheck.size() ;i++){
                    reverse += junkCheck[l]; //stressed
                    l--;
                }
                dic.word = reverse;
                if(reverse == endWord){ 
                    endWordIndex = dictVect.size();
                }
                else if(reverse == beginWord){
                    beginWordIndex = dictVect.size();
                }
                dictVect.push_back(dic);
            }
            //check for []
            if(!specialChar){
                size_t brackCheck = junkCheck.find("[");
                if(brackCheck !=std::string::npos){
                    specialChar = true;
                    size_t closeBrack = junkCheck.find("]");
                    string brack = junkCheck.substr(brackCheck+1, closeBrack-brackCheck-1); //[oer] brack = oer
                    if(brackCheck == 0){ //brackest is first char
                        if(closeBrack == junkCheck.size()-1){// [ao]
                            for(size_t n = 0; n < brack.size(); n++){
                                dic.word = brack[n];
                                if(dic.word == endWord){ 
                                endWordIndex = dictVect.size();
                                }
                                else if(dic.word == beginWord){
                                beginWordIndex = dictVect.size();
                                } 
                                dictVect.push_back(dic);
                            }
                        }
                        else{//[ao]ple
                            for(size_t n = 0; n < brack.size(); n++){
                                string copy = "";
                                copy += brack[n];
                                copy += junkCheck.substr(closeBrack + 1);
                                dic.word = copy;
                                if(copy == endWord){ 
                                endWordIndex = dictVect.size();
                                }
                                else if(copy == beginWord){
                                beginWordIndex = dictVect.size();
                                } 
                                dictVect.push_back(dic);
                            }
                        }
                    }
                    else{//bracket isn't first char
                        if(closeBrack == junkCheck.size()-1){// ch[io]
                            for(size_t n = 0; n < brack.size(); n++){
                                string copy = "";
                                copy+= junkCheck.substr(0, brackCheck);
                                copy+= brack[n];
                                dic.word = copy;
                                if(copy == endWord){ 
                                endWordIndex = dictVect.size();
                                }
                                else if(copy == beginWord){
                                beginWordIndex = dictVect.size();
                                } 
                                dictVect.push_back(dic);
                            }
                        }
                        else{//ch[io]p
                            for(size_t n = 0; n < brack.size(); n++){
                                string copy = "";
                                copy += junkCheck.substr(0, brackCheck);
                                copy += brack[n];
                                copy += junkCheck.substr(closeBrack+1);
                                dic.word = copy;
                                if(copy == endWord){ 
                                endWordIndex = dictVect.size();
                                }
                                else if(copy == beginWord){
                                beginWordIndex = dictVect.size();
                                } 
                                dictVect.push_back(dic);
                            }
                        }
                    }
                    /*
                    junkCheck.erase(brackCheck, 1); //tre[an]d --> trean]d
                    junkCheck.erase(closeBrack-1,1); //treand
                    string copy = junkCheck.substr(0, brackCheck);
                    for(size_t j = 0; j < brack.size(); j++){
                        copy+= brack[j];
                        if(junkCheck.find("]") != junkCheck.size()-1){

                            copy+= junkCheck.substr(closeBrack + 1);
                        }
                        dic.word = copy;
                        if(copy == endWord){ 
                        endWordIndex = dictVect.size();
                        }
                        else if(copy == beginWord){
                        beginWordIndex = dictVect.size();
                        
                        }
                        dictVect.push_back(dic);
                    }
                    */
                }
            }
            //check for !
            if(!specialChar){
                size_t excCheck = junkCheck.find("!");
                if(excCheck !=std::string::npos){
                    specialChar = true;
                    size_t firstLetIndex = excCheck - 2;
                    size_t secLetIndex = excCheck - 1;
                    //delete exclaim
                    junkCheck.erase(excCheck, 1);
                    //add to dict
                    dic.word = junkCheck;
                    if(junkCheck == endWord){ 
                    endWordIndex = dictVect.size();
                        }
                    else if(junkCheck == beginWord){
                    beginWordIndex = dictVect.size();
                    }
                    dictVect.push_back(dic);
                    //swap in junkCheck
                    char temp = junkCheck[firstLetIndex];
                    junkCheck[firstLetIndex] = junkCheck[secLetIndex];
                    junkCheck[secLetIndex] = temp;
                    dic.word = junkCheck;   //need separate Dictionary object??
                    if(junkCheck == endWord){ 
                    endWordIndex = dictVect.size();
                    }
                    else if(junkCheck == beginWord){
                    beginWordIndex = dictVect.size();
                    }
                    dictVect.push_back(dic);
                }
            }
            //check for ?
            if(!specialChar){
                size_t quesCheck = junkCheck.find("?"); //lets?tmon = 4
                    if(quesCheck !=std::string::npos){
                        specialChar = true;
                        char dup = junkCheck[quesCheck - 1]; //s
                        junkCheck.erase(quesCheck, 1); //letstmon
                        dic.word = junkCheck;
                        if(junkCheck == endWord){ 
                        endWordIndex = dictVect.size();
                        }
                        else if(junkCheck == beginWord){
                        beginWordIndex = dictVect.size();
                        } 
                        dictVect.push_back(dic);
                        string copy = junkCheck.substr(0, quesCheck);//lets
                        copy += dup;//letss
                        copy+= junkCheck.substr(quesCheck, junkCheck.size()-quesCheck);//letstmon
                        dic.word = copy;
                        if(copy == endWord){ 
                            endWordIndex = dictVect.size();
                        }
                        else if(copy == beginWord){
                        beginWordIndex = dictVect.size();
                        }
                        dictVect.push_back(dic);
                    }
            }
            if(!specialChar){//no special character, just add
                dic.word = junkCheck;
                if(junkCheck == endWord){ 
                    endWordIndex = dictVect.size();
                }
                else if(junkCheck == beginWord){
                    beginWordIndex = dictVect.size();
                }
                dictVect.push_back(dic);
            }
            cin >> junkCheck;
            }
        }
        dictSize = dictVect.size();
        indexVect.reserve(dictSize);
        lettVect.reserve(dictSize);
        morphVect.reserve(dictSize);
        bool bWordPresent = false;
        for(size_t n = 0; n < dictSize; n++){
            if(dictVect[n].word == beginWord){
                bWordPresent = true;
            }
        }
        if(!bWordPresent){
            cerr << "Error: Beginning word does not exist in the dictionary\n";
            exit(1);
        }
        bool eWordPresent = false;
        for(size_t n = 0; n < dictSize; n++){
            if(dictVect[n].word == endWord){
                eWordPresent = true;
            }
        }
        if(!eWordPresent){
            cerr << "Error: Ending word does not exist in the dictionary\n";
            exit(1);
        }
        return;
    }

    void search(){
        //to check if two words are similar, write code that loops through two strings, comparing one character from the first string to one character from the second
        deque<size_t> sC; 
        sC.push_front(beginWordIndex);
        dictVect[beginWordIndex].found = true;
        currentWord = beginWordIndex;
        bool endFound = false;
        bool scEmpty = false;
        while(!endFound && !scEmpty){//until end word is discovered or search container is empty when attempt to fetch next word is made
            if(sC.size() != 0){
                if(stackMode){
                    //cout << dictVect[currentWord].word << endl;
                    currentWord = sC.back();
                    sC.pop_back();
                }
                else{
                    currentWord = sC.front();
                    sC.pop_front();
                }
                for(size_t n = 0; n < dictSize; n++){
                    if(!dictVect[n].found){
                        bool canMorph = false;
                    //check if word can be morphed into 
                    if(change){
                        canMorph = changeFunc(n,false);
                    }
                    if(len && !dictVect[n].found && !canMorph){
                        canMorph = remove(n, false);
                        if(!canMorph){
                            canMorph = add(n, false);
                        } 
                    }
                    if(swap && !dictVect[n].found && !canMorph){
                        canMorph = swapFunc(n, false);
                    }
                    //if yes, add to search container
                    if(canMorph){
                        sC.push_back(n);
                    }
                    //check if found end word
                    if(n == endWordIndex && dictVect[n].found){
                        endFound = true;
                    }
                    }//if

                    if(endFound){
                        n = dictSize;
                    }
                }
                                /*while(n < dictSize && !endFound){
                            //for(size_t n = 0; n < dictVect.size(); n++){
                                if(!dictVect[n].found){
                                    bool canMorph = false;
                                    //check if word can be morphed into 
                                    if(change){
                                        canMorph = changeFunc(n,false);
                                    }
                                    if(len && !dictVect[n].found && !canMorph){
                                        canMorph = remove(n, false);
                                        if(!canMorph){
                                            canMorph = add(n, false);
                                        } 
                                    }
                                    if(swap && !dictVect[n].found && !canMorph){
                                        canMorph = swapFunc(n, false);
                                    }
                                    //if yes, add to search container
                                    if(canMorph){
                                        sC.push_back(n);
                                    }
                                    //check if found end word
                                    if(n == endWordIndex && dictVect[n].found){
                                        endFound = true;
                                    }
                                }//if
                            //}    //for
                            n++;
                                }*/
            }
            if(sC.size()==0){
                scEmpty = true;
            }
        }   
        if(!endFound){
            endNotFoundPrint = true;
        }
        return;
    }
    

    void output(){
        if(endNotFoundPrint){
            int count = 0;
            for(size_t n = 0; n < dictSize; n++){
                if(dictVect[n].found){
                    count++;
                } 
            }
            cout << "No solution, " << count << " words discovered.";
            return;
        }
        else{
            backTrace();
            if(outFormat == 0){
                //cout << "Words in morph: " << morphCount + 1 << "\n";
                cout << "Words in morph: " << totalCount + 1 << "\n";

                //cout << dictVect[beginWordIndex].word << "\n";
                vector<string> copyVect;
                //copyVect.reserve(morphCount);
                copyVect.reserve(totalCount+1);
                copyVect.push_back(dictVect[endWordIndex].word);
                size_t indUpdate = endWordIndex;
                for(int n = 0; n < totalCount; n++){
                    //go through dictionary backwards, traversing through previous
                    copyVect.push_back(dictVect[dictVect[indUpdate].prev].word);
                    indUpdate = dictVect[indUpdate].prev;
                }
                for(auto it = copyVect.rbegin(); it != copyVect.rend(); it++){
                    cout << *it << "\n";
                }

                
            }
            else{
                cout << "Words in morph: " << totalCount + 1<< "\n"; ///
                
                cout << dictVect[beginWordIndex].word << "\n";
                size_t j = lettVect.size()-1;
                for(int n = totalCount-1; n>=0; n--){
                    if(morphVect[n] == 'd' || morphVect[n] == 's'){ //CURRENT ERROR W STUFF IN JSON //////////////////////////////////////////
                        cout << morphVect[n] << "," << indexVect[n] << "\n";
                        j = j+1;
                    }
                    else{
                        cout << morphVect[n] << "," << indexVect[n] << "," << lettVect[j] << "\n";
                    }
                    j--;
                } //morph delete and swap dont have lett
            }
        }
        return;
        
    }
};
    

