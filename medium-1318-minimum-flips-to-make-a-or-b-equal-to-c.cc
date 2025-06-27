//🔹 Bitwise Strategy:
//Loop over each bit position (0 to 31) and for each bit:

//If c_i == 0, we must flip any 1s in a_i or b_i to 0.

//If c_i == 1, and both a_i and b_i are 0, we must flip one of them to 1.

int minFlips(int a, int b, int c) {
    int flips = 0;
    for (int i = 0; i < 32; ++i) {
        int bitA = (a >> i) & 1;
        int bitB = (b >> i) & 1;
        int bitC = (c >> i) & 1;

        if ((bitA | bitB) != bitC) {
            if (bitC == 0)
                flips += bitA + bitB; // both need to be 0
            else
                flips += 1; // both are 0, need one flip
        }
    }
    return flips;
}
//🔹 Time & Space:
//Time: O(1) (32 bits max)

//Space: O(1)

