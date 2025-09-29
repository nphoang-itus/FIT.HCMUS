//// CHECKED PROPERTY
const myCheckBox = document.getElementById("myCheckBox");
const visaBtn = document.getElementById("visaBtn");
const masterCardBtn = document.getElementById("masterCardBtn");
const paypalBtn = document.getElementById("paypalBtn");
const mySubmit = document.getElementById("mySubmit");
const subResult = document.getElementById("subResult");
const paymentResult = document.getElementById("paymentResult");

mySubmit.onclick = function() {
  if (myCheckBox.checked) {
    subResult.textContent = `Chắc chắn là Hoàng đẹp trai rồi!`;
  } else {
    subResult.textContent = `Quên tick cho Hoàng đep trai kìa!`;
  }

  if (visaBtn.checked) {
    paymentResult.textContent = `Sure luôn anh T 6`;
  } else if (masterCardBtn.checked) {
    paymentResult.textContent = `Sure luôn Chi khó tánh`;
  } else if (paypalBtn.checked) {
    paymentResult.textContent = `Tất cả đúng là chắc`;
  } else {
    paymentResult.textContent = `Chọn đi mài`;
  }
}