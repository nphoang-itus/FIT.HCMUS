//// 01 - INTRO
// // In ra màn hình
// console.log("Hello");
// console.log("I like dog");

// // Hiển thị cảnh báo
// // window.alert("This is an alert!");

// // Comment
// // Dùng // hoặc
// /*
//   This is a comment
// */

// Thay đổi nội dung thẻ bằng lệnh JS
// document.getElementById("myH1").textContent = "Hello";
// document.getElementById("myP").textContent = "i like dog!"

//// 02 - VARIABLE
// let x; // x = undefined
// x = 100; // let x = 100;

// console.log(x);

// let age = 20;
// console.log(`you are ${age} year old`);

// let price = 10.22;
// console.log(`the price is $${price}`);

// // in ra loại biến
// console.log(typeof x);
// console.log(typeof age);


// Kiểu dữ liệu string
// let firstName = "Phuc Hoang";
// console.log(`my first name is ${firstName}`);
// console.log(typeof firstName);

// Kiểu dữ liệu Boolean
// let online = true;
// console.log(typeof online)
// console.log(`i'm online?: ${online}`)

// let fullName = "Nguyen Phuc Hoang";
// document.getElementById("p1").textContent = fullName;
// document.getElementById("p1").textContent = firstName;
// document.getElementById("p3").textContent = online;

//// 03 - ARITHMETIC OPERATORS
// = operand(values, variable, etc,...)
// = operators (+ - * /)

// let students = 12;

// students = students / 5;
// students = students % 5;
// students /= 3;
// students++;

// students = students ** 3; // 12 ^ 3
// console.log(students);

/**
 * operator precedence
 * parenthesis ()
 * exponents
 * multiplication & division & modulo
 * addition & subtraction
 */

// let result = 2 + 3 ** 4 + (1 + 3 * 4);
// console.log(result);

//// ACCEPT USER INPUT
// 1. EASE WAY: window prompt
// let username = window.prompt("What's your user name");
// console.log(username);

//2. PROFESSIONAL WAY = HTML TextBox
// let username;
// document.getElementById("mySubmit").onclick = function() {
//   username = document.getElementById("myText").value;
//   document.getElementById("myH1").textContent = `Hello ${username}`;
//   console.log(username);
// }

//// TYPE CONVERSION: change the datatype of a value to another (strings, numbers, booleans)
// let age = window.prompt("How old r u?"); // nếu nhập vào 20
// // age = Number(age);
// age += 1;
// console.log(age, typeof age); // in ra 201 => cần chuyển nhập chuỗi về dạng số

// let x = "";
// let y = "";
// let z = "";

// x = Number(x);
// y = String(y);
// z = Boolean(z);

// console.log(x, typeof x); // NaN
// console.log(y, typeof y); // "pizza"
// console.log(z, typeof z); // true

//// CONSTANTS
// const PI = 3.14159;
// let radius = 12;
// let circumference = 2 * PI * radius;
// console.log(circumference);

// document.getElementById("mySubmit").onclick = function() {
//   radius = document.getElementById("myText").value;
//   radius = Number(radius);
//   let circumference = 2 * PI * radius;
//   document.getElementById("myH3").textContent = circumference + "cm";
// }

//// COUNTER PROGRAM