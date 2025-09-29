//// MATH OBJECT

// let x = 2.54;
// let y = 2;
// let z;

// z = Math.round(x); // round làm tròn xuống khi x < x.5 còn làm tròn lên khi x > x.5
// // floor luôn làm tròn xuống, ceil luôn làm tròn lên
// console.log(z);

// x = 3, y = 2;
// z = Math.pow(x, y);
// z = Math.max(x, y);
// z = Math.min(x, y);
// console.log(z);

//// RANDOM NUMBER GENERATOR
// let randomNum = Math.random(); // ran từ 0 -> 1
// console.log(randomNum);

// let randomNum = Math.floor(Math.random() * 6) + 1; // ran từ 1 -> 6 (nguyên)
// console.log(randomNum);

// let min = 50;
// let max = 100;
// let randomNumber = Math.floor(Math.random() * (max - min)) + min;
// console.log(randomNumber);

// // RANDOM NUMBER PROGRAM
// const myButton = document.getElementById("myButton");
// const myLabel = document.getElementById("myLabel");

// myButton.onclick = function() {
//   let min = 50;
//   let max = 100;
//   let randomNumber = Math.floor(Math.random() * (max - min)) + min;
//   myLabel.textContent = randomNumber;
// }

// //// IF STATEMENT
// const myInput = document.getElementById("myInput");
// const myButton = document.getElementById("myButton");
// const myInfo = document.getElementById("myInfo");

// let age = 0;

// myButton.onclick = function() {
//   age = myInput.value;
//   age = Number(age);

//   if (age < 0) {
//     myInfo.textContent = `Tuổi không hợp lệ`;
//   } else if (age < 18) {
//     myInfo.textContent = `Mày quá non`;
//   } else if (age <= 20) {
//     myInfo.textContent = `${age} tuổi, Trẻ đẹp`;
//   } else {
//     myInfo.textContent = `Quá già`;
//   }
// }