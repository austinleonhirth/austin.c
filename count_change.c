/*
    Prints the number of ways to make change for a given amount of money in USD
    Gather input(amount in USD) from user then calculate the number of ways to make change
    for that amount of money using quarters, dimes, nickels, and pennies.
*/

#define ANSI_COLOR_Bright_Green "\x1b[92m"
#define ANSI_COLOR_RESET "\x1b[0m"

int count_change(double amount){
    int count = 0;
    int amountCents = (int)(amount * 100 + 0.5);

    for(int p = 0; p <= (amountCents); p++){
        for(int n = 0; n <= (amountCents-p)/5; n++){
            for(int d = 0; d <= (amountCents-n*5)/10; d++){
                for(int q = 0; q <= (amountCents-d*10)/25; q++){

                    if(amountCents == p + 5*n + 10*d + 25*q){
                        count++;
                    }

                }
            }
        }
    }
    return count;
}

// Main function for this feature, handles user input and calls count_change
void count_change_f(){
    double amount;
    printf("Enter amount in USD: $");

    //with error handling, get amount from user
    while(scanf("%lf", &amount) != 1){
        printf("Invalid input. Enter amount in USD: $");
        while(getchar() != '\n');
    }
    printf("Number of ways to make change: "ANSI_COLOR_Bright_Green"%d\n\n"ANSI_COLOR_RESET, count_change(amount));
}