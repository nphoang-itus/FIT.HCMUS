const express = require('express');
const app = express();

// Render sẽ cung cấp biến PORT, ta dùng nó
const PORT = process.env.PORT || 3000;

app.get('/', (req, res) => {
  res.send('Hello Render! Đây là demo Node.js đầu tiên của tôi 🚀');
});

app.listen(PORT, () => {
  console.log(`Server đang chạy tại cổng ${PORT}`);
});