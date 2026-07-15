class Solution {
public:
    int gcdOfOddEvenSums(int n) {
        int sumodd=n*n;
        int sumeven=n*(n+1);
        while(sumeven !=0){
            int temp=sumeven;
            sumeven=sumodd%sumeven;
            sumodd=temp;
        }
        return sumodd;
    }
};