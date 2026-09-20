// bonus for median
// double median()
// {
//     double copy[MAX_SIZE];
//     for (int i = 0; i < size; i++)
//     {
//         copy[i] = arr[i];
//     }
//     for (int i = 0; i < size - 1; i++)
//     {
//         for (int j = i + 1; j < size; j++)
//         {
//             if (copy[j] < copy[i])
//             {
//                 double temp = copy[i];
//                 copy[i] = copy[j];
//                 copy[j] = temp;
//             }
//         }
//     }
//     if (size % 2 == 1)
//     {
//         return copy[size / 2];
//     }
//     else
//     {
//         return (copy[size / 2 - 1] + copy[size / 2]) / 2.0;
//     }
// }