let userName = "nphoang    ";

console.log(userName.charAt(2)); // trả về ký tự ở vị trí
console.log(userName.indexOf('n')); // trả về vị trí đầu tiên của ký tự (ko thấy trả về -1)
console.log(userName.lastIndexOf('n')); // trả về vị trí cuối cùng của ký tự (ko thấy trả về -1)
console.log(userName.length);
console.log(userName.trim()); // xoá dấu cách thừa ở 2 bên
console.log(userName.toUpperCase());
console.log(userName.repeat(3)); // lặp chuỗi 3 lần
console.log(userName.startsWith("nph"));
console.log(userName.replaceAll(' ', ',')); // thay tất cả dấu cách bằng dấu phẩy