#include <iostream>

using namespace std;

int forward(int input, int rotor[26], int state)
{
    return rotor[(input + state) % 26]; 
}

int backward(int input, int rotor[26], int state)
{
    return (rotor[input] - state + 26) % 26;
}

int main()
{

    //0 1	2	3	4	5	6	7	8	9	10	11	12	13	14	15	16	17	18	19	20	21	22	23	24	25
    //a	b	c	d	e	f	g	h	i	j	k	l	m	n	o	p	q	r	s	t	u	v	w	x	y	z    

    int rotor1[26] = {4,10,12,5,11,6,3,16,21,25,13,19,14,22,24,7,23,20,18,15,0,8,1,17,2,9}; //EKMFLGDQVZNTOWYHXUSPAIBRCJ
    int rotor2[26] = {0,9,3,10,18,8,17,20,23,1,11,7,22,19,12,2,16,6,25,13,15,24,5,21,14,4}; //AJDKSIRUXBLHWTMCQGZNPYFVOE
    int rotor3[26] = {1,3,5,7,9,11,2,15,17,19,23,21,25,13,24,4,8,22,6,0,10,12,20,18,16,14}; //BDFHJLCPRTXVZNYEIWGAKMUSQO

    int rotor1I[26] = {20,22,24,6,0,3,5,15,21,25,1,4,2,10,12,19,7,23,18,11,17,8,13,16,14,9}; 
    int rotor2I[26] = {0,9,15,2,25,22,17,11,5,1,3,10,14,19,24,20,16,6,4,13,7,23,12,8,21,18};
    int rotor3I[26] = {19,0,6,1,15,2,18,3,16,4,20,5,21,13,25,7,24,8,23,9,22,11,17,10,14,12};

    int reflector[26] = {4,9,12,25,0,11,24,23,21,1,22,5,2,17,16,20,14,13,19,18,15,8,10,7,6,3};

    int rotorState[3] = {0,0,0}; //rotor1, rotor2, rotor3;

    bool endStatus = true;
    while(endStatus)
    {
        string numAlpha[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m", "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

        cout << ": ";
        string inputString;
        cin >> inputString;

        int input = 0;

        for(int i = 0; i < 26; ++i)
        {
            if(inputString == numAlpha[i])
            {
                input = i;
            }
            //todo: if not accetable 
        }

        if(input == 777)
        {
            endStatus = false;
        }
        else if(input < 0 || input > 25)
        {
            cout << "How dare you. I hate " << input << "!!!" << endl;
        }
        else
        {
            forward(input, rotor2, rotorState[1]);

            int output = forward(forward(forward(input, rotor1, rotorState[0]), rotor2, rotorState[1]), rotor3, rotorState[2]);
            output = reflector[output];
            output = backward(backward(backward(output, rotor3I, rotorState[2]), rotor2I, rotorState[1]), rotor1I, rotorState[0]);
            
            string outputString = numAlpha[output];

            cout << outputString << endl;
        }

        int rotorStateNum = rotorState[0] + (rotorState[1] * 26) + (rotorState[2] * (26 * 26));
        rotorStateNum = (rotorStateNum + 1) % (26 * 26 * 26);
        
        rotorState[2] = rotorStateNum / (26 * 26);
        rotorStateNum = rotorStateNum % (26 * 26);

        rotorState[1] = rotorStateNum / (26);
        rotorStateNum = rotorStateNum % (26);

        rotorState[0] = rotorStateNum;
    }
    return 0;
}