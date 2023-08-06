// Obviously this does not compile
// This is a nice sorting algoritm to sort by order
// Steal this code instead of thinking of how to solve this
for (i = 0; i < numbersSize - 1; ++i) {

   // Find index of smallest remaining element
   indexSmallest = i;
   for (j = i + 1; j < numbersSize; ++j) {

      if (numbers[j] < numbers[indexSmallest]) {
         indexSmallest = j;
      }
   }

   // Swap numbers[i] and numbers[indexSmallest]
   temp = numbers[i];
   numbers[i] = numbers[indexSmallest];
   numbers[indexSmallest] = temp;
}
