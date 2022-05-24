#include <iostream>
#include <stack>

using namespace std;

struct FCall
{
    int n;                        // the function parameter.
    int result = 0;               // hold the return value of the function.
    int a = 0, b = 0, d = 0;      // local variables of the function that will be used.
    string name;                  // hold the recursive call name to distinguish between a or b or d.
    int stage = 0;                // stage equals zero means the first call (not recurse yet) and will need to resume the function.
                                  // the stage needed since there is processes needed to be done after recursive call.
};

int FIterative(int n)
{
    int finalR = 0;                //storing the final result(return value).

    FCall fcall;                  //for the first call to the function.
    fcall.n = n;

    stack <FCall> s;
    s.push(fcall);

    FCall ca;                     //for the recursive call in equation a.   F(n-1)
    FCall cb;                     //for the recursive call in equation b.   F(n/2)
    FCall cd;                     //for the recursive call in equation d.   F(n)

    while(!s.empty())
    {
        FCall call = s.top();
        s.pop();

        if (call.stage == 0)        // first call to the function
        {
            if (call.n <= 1)        // base case
            {
                // store 1 in the right result variable for each recursive call.
                if (call.name == "cd")
                    cd.result = 1;

                else if (call.name == "cb")
                    cb.result = 1;

                else if (call.name == "ca")
                    ca.result = 1;

                else
                {
                    call.result = 1;
                    finalR = 1;
                }
            }
            else
            {
                call.stage = 1;             // to resume the call since stage 1 is for equation a.
                s.push(call);

                // preparing equation a.
                ca.n = call.n - 1;
                ca.name = "ca";
                s.push(ca);
            }
        }

        else if (call.stage == 1)
        {
            call.stage = 2;                 // to resume the call since stage 2 is for equation b.
            call.a = call.n + ca.result;    // calculate the equation a.
            call.result = call.a;           // store the result of equation a to the total result.
            s.push(call);

            // preparing equation b.
            cb.n = call.n / 2;
            cb.name = "cb";
            s.push(cb);
        }

        else if (call.stage == 2)
        {
            call.stage = 3;                // to resume the call since stage 3 is for equation d.
            call.b = call.n * cb.result;   // calculate the equation b.
            call.result += call.b;         // add the result of equation b to the total result.
            s.push(call);

            // calculate the equation c.
            int c = call.n - 2 - ((call.a + call.b) % 2);

            // preparing equation d.
            cd.n = c;
            cd.name = "cd";
            s.push(cd);
        }

        else if (call.stage == 3)
        {
            call.stage = -1;              // to end the call since stage -1 means we reach the end of the function call.
            call.d = cd.result;           // store the result of the recursive f(c) in the equation d.
            call.result += call.d;        // add the result of equation d to the total result.
            s.push(call);

            // get the right result value for each recursive call and store it in its result variable.
            if (call.name == "ca")
                ca.result = call.result;

            else if (call.name == "cb")
                cb.result = call.result;

            else if (call.name == "cd")
                cd.result = call.result;

            finalR  = call.result;            // store the result in the return variable.
        }
    }
    return finalR;
}

int main()
{
    int result;

    for(int i = 0; i < 20; i++)
    {
        result = FIterative(i);
        cout << "if n = " <<  i  << " , the result of the function will be " << result << endl;
    }
    /*
    result = FIterative(0);
    cout << "if n = 0  , the result of the function will be " << result << endl;

    result = FIterative(1);
    cout << "if n = 1  , the result of the function will be " << result << endl;

    result = FIterative(2);
    cout << "if n = 2  , the result of the function will be " << result << endl;

    result = FIterative(3);
    cout << "if n = 3  , the result of the function will be " << result << endl;

    result = FIterative(4);
    cout << "if n = 4  , the result of the function will be " << result << endl;

    result = FIterative(5);
    cout << "if n = 5  , the result of the function will be " << result << endl;

    result = FIterative(6);
    cout << "if n = 6  , the result of the function will be " << result << endl;

    result = FIterative(7);
    cout << "if n = 7  , the result of the function will be " << result << endl;

    result = FIterative(8);
    cout << "if n = 8  , the result of the function will be " << result << endl;

    result = FIterative(9);
    cout << "if n = 9  , the result of the function will be " << result << endl;

    result = FIterative(10);
    cout << "if n = 10 , the result of the function will be " << result << endl;

    result = FIterative(11);
    cout << "if n = 11 , the result of the function will be " << result << endl;

    result = FIterative(12);
    cout << "if n = 12 , the result of the function will be " << result << endl;

    result = FIterative(13);
    cout << "if n = 13 , the result of the function will be " << result << endl;

    result = FIterative(14);
    cout << "if n = 14 , the result of the function will be " << result << endl;

    result = FIterative(15);
    cout << "if n = 15 , the result of the function will be " << result << endl;

    result = FIterative(16);
    cout << "if n = 16 , the result of the function will be " << result << endl;

    result = FIterative(17);
    cout << "if n = 17 , the result of the function will be " << result << endl;

    result = FIterative(18);
    cout << "if n = 18 , the result of the function will be " << result << endl;

    result = FIterative(19);
    cout << "if n = 19 , the result of the function will be " << result << endl;

    result = FIterative(20);
    cout << "if n = 20 , the result of the function will be " << result << endl;
*/
    return 0;
}
