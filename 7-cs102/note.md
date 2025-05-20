# 08:45 – 09:25 [Keynote 1] Native vs. Cross-Platform: Technology, Trends & Market Insights
### 1. **Native App là gì?**

* Ứng dụng **được phát triển riêng cho một hệ điều hành cụ thể** (Android hoặc iOS).
* Viết bằng ngôn ngữ và SDK chính thức do nhà phát triển hệ điều hành cung cấp:

  * **iOS**: Swift hoặc Objective-C với Xcode.
  * **Android**: Kotlin hoặc Java với Android Studio.

#### Ưu điểm:

* Hiệu năng cao: Gần như tương đương phần mềm viết bằng C/C++ chạy trực tiếp trên hệ thống.
* Trải nghiệm người dùng tối ưu, tương thích 100% với giao diện gốc (native UI/UX).
* Tận dụng tối đa API hệ thống như cảm biến, camera, ARKit, v.v.

#### Nhược điểm:

* Phải phát triển riêng cho từng nền tảng → **chi phí và thời gian gấp đôi**.
* Bảo trì phức tạp: mỗi bản sửa lỗi hay nâng cấp phải làm cho từng nền tảng.

---

### 2. **Cross-Platform App là gì?**

* Ứng dụng **viết một lần, chạy trên nhiều nền tảng**, thường thông qua **framework trung gian**.
* Các công nghệ phổ biến:

  * **Flutter** (Dart)
  * **React Native** (JavaScript)
  * **Xamarin** (C#)
  * **MAUI** của Microsoft
  * **Capacitor/Ionic** (WebView-based hybrid app)

#### Cơ chế hoạt động:

* Một số framework như **Flutter** vẽ giao diện riêng trên canvas nên không phụ thuộc UI hệ thống.
* **React Native** dùng “bridge” để chuyển tiếp lệnh từ JavaScript sang native code.

#### Ưu điểm:

* **Tiết kiệm chi phí và thời gian** phát triển do dùng chung codebase (\~70–90%).
* Cộng đồng đông, tài nguyên nhiều, dễ học hơn đối với lập trình viên web.
* Dễ dàng đồng bộ tính năng giữa các nền tảng.

#### Nhược điểm:

* Hiệu năng không bằng native (do layer trung gian hoặc bridge).
* Đôi khi phải viết **plugin native thủ công** nếu framework chưa hỗ trợ.
* UX đôi khi lệch chuẩn nếu không tối ưu từng nền tảng.

---

## II. **Trends (Xu hướng công nghệ mới nhất)**

### 1. **Flutter thống trị mảng cross-platform**

* Được Google hỗ trợ, **Flutter** có tốc độ phát triển nhanh, hỗ trợ tốt cả iOS, Android, Web và Desktop.
* Nhiều công ty lớn (Alibaba, BMW, eBay...) đang chuyển qua dùng Flutter.

### 2. **React Native vẫn giữ vững vị thế**

* Do Meta phát triển, phù hợp với lập trình viên web.
* Được dùng trong nhiều ứng dụng phổ biến như Facebook, Instagram, Discord, v.v.

### 3. **Tăng trưởng của các hybrid framework mới**

* **Microsoft MAUI** (Multi-platform App UI) – kế nhiệm Xamarin, hỗ trợ tốt trên Windows.
* **Capacitor** (Tích hợp tốt với ứng dụng web hiện có – cho developer JavaScript).

### 4. **Rise of PWA (Progressive Web App)**

* Web app nâng cao, có thể hoạt động offline, giống app nhưng không cần cài đặt từ store.
* Dù chưa thể thay thế native hoàn toàn nhưng đang **trở thành xu hướng cho ứng dụng đơn giản**.

---

## III. **Market Insights (Nhìn nhận từ thị trường và kinh doanh)**

### 1. **Lựa chọn nền tảng phụ thuộc vào mục tiêu kinh doanh**

| Mục tiêu                                             | Khuyến nghị                            |
| ---------------------------------------------------- | -------------------------------------- |
| MVP, startup, ra mắt nhanh                           | Cross-platform (Flutter, React Native) |
| Ứng dụng đòi hỏi hiệu năng cao (game, AR, streaming) | Native                                 |
| Ứng dụng nội bộ công ty, không public store          | Web app hoặc PWA                       |

### 2. **Thống kê sử dụng thực tế**

* Theo báo cáo từ Stack Overflow & GitHub:

  * Flutter: tăng trưởng mạnh nhất về số lượng repo và câu hỏi.
  * React Native: dẫn đầu về số lượng ứng dụng đang hoạt động.
* Theo báo cáo từ App Annie:

  * Các ứng dụng top đầu trên iOS/Android vẫn chủ yếu viết bằng native.

### 3. **Chi phí và nguồn lực**

* **Native**:

  * Cần 2 đội phát triển riêng (iOS và Android).
  * Bảo trì, kiểm thử, cập nhật phức tạp.
* **Cross-platform**:

  * Một đội phát triển chung, tiết kiệm 30–50% chi phí.
  * Tuy nhiên vẫn cần developer hiểu native để xử lý bug hoặc tích hợp plugin.

---

## Kết luận

* **Không có lựa chọn "tốt nhất tuyệt đối"**, mà chỉ có lựa chọn **phù hợp với mục tiêu**.
* **Chiến lược Hybrid**: Nhiều công ty chọn phát triển bằng cross-platform nhưng giữ lại một số module native riêng cho hiệu suất cao (ví dụ camera, xử lý video...).
* **Dự đoán tương lai**: Với sự phát triển của Flutter và sự tối ưu của phần cứng mobile, cross-platform sẽ tiếp tục tăng trưởng, nhưng native vẫn là tiêu chuẩn cho ứng dụng cao cấp.

---

## Note
- OOP (Kiến trúc) , MMT, HĐH (Tiến trình)
- 

# 09:25 – 09:35 Break

# 09:35 – 10:15 [Keynote 2] AI in Mobile: Cloud vs. Edge, Use Cases & Cost-Saving Tips
## I. **Cloud AI vs. Edge AI: Khái niệm và so sánh kỹ thuật**

### 1. **Cloud AI là gì?**

* AI được xử lý **trên server từ xa (cloud)**, ví dụ như Google Cloud AI, AWS SageMaker, OpenAI API...
* Thiết bị gửi dữ liệu (hình ảnh, giọng nói...) lên cloud → xử lý → trả kết quả về.

#### Ưu điểm:

* Sức mạnh tính toán lớn, có thể chạy các mô hình nặng như GPT-4, LLMs, Stable Diffusion...
* Dễ cập nhật mô hình, triển khai mô hình mới, huấn luyện từ xa.

#### Nhược điểm:

* Phụ thuộc vào kết nối mạng (latency cao).
* Chi phí cao (hạ tầng cloud, tính phí theo số request).
* Rủi ro bảo mật nếu truyền dữ liệu nhạy cảm (gương mặt, giọng nói…).

---

### 2. **Edge AI là gì?**

* AI chạy trực tiếp **trên thiết bị đầu cuối** (smartphone, tablet, wearable...).
* Ví dụ: nhận diện khuôn mặt trên iPhone (FaceID), xử lý ảnh bằng Google Lens offline.

#### Ưu điểm:

* Phản hồi tức thì, độ trễ thấp.
* Không cần kết nối internet.
* Bảo mật tốt hơn (dữ liệu không rời khỏi thiết bị).
* Giảm chi phí vận hành server.

#### Nhược điểm:

* Hạn chế tài nguyên phần cứng (RAM, CPU, GPU).
* Không thể chạy mô hình AI quá lớn → cần tối ưu (quantization, pruning…).

---

### 3. **So sánh tổng quan**

| Tiêu chí        | Cloud AI              | Edge AI                     |
| --------------- | --------------------- | --------------------------- |
| Tính toán       | Mạnh (GPU/TPU)        | Hạn chế (tùy thiết bị)      |
| Độ trễ          | Có (vì truyền mạng)   | Rất thấp (xử lý tại chỗ)    |
| Bảo mật dữ liệu | Có nguy cơ rò rỉ      | An toàn hơn                 |
| Chi phí dài hạn | Cao                   | Thấp hơn                    |
| Phù hợp với     | LLMs, các mô hình lớn | Xử lý nhanh, nhẹ, real-time |

---

## II. **Use Cases: Ứng dụng thực tế của AI trên mobile**

### 1. **Ứng dụng sử dụng Cloud AI**

* **Chatbot AI (ChatGPT, Gemini)**: gửi câu hỏi đến cloud, trả về phản hồi.
* **Nhận dạng giọng nói online**: Google Speech API, Whisper.
* **Phân tích ảnh chuyên sâu (y tế, vật thể)**: cloud inference trả kết quả.
* **Tìm kiếm ngữ nghĩa (semantic search)** trong ứng dụng học tập, bán hàng…

### 2. **Ứng dụng sử dụng Edge AI**

* **Mở khóa khuôn mặt (Face ID, Samsung Face Unlock)**.
* **Camera thông minh**: Làm mờ hậu cảnh, nhận diện vật thể, filter AR...
* **Gợi ý bàn phím (Gboard)**: AI gợi ý văn bản theo ngữ cảnh.
* **Phân loại ảnh trong album**: phân loại theo gương mặt, vật thể, vị trí...

### 3. **Ứng dụng Hybrid (kết hợp Cloud + Edge)**

* Edge xử lý sơ bộ, gửi kết quả đã được rút gọn lên cloud để phân tích sâu.
* Ví dụ:

  * Ứng dụng y tế: phân tích ban đầu bằng Edge → gửi lên cloud để xác nhận bệnh.
  * Chatbot mobile: AI trên thiết bị phân tích ý định, cloud xử lý nội dung.

---

## III. **Cost-Saving Tips: Chiến lược tiết kiệm chi phí**

### 1. **Chuyển từ cloud sang edge nếu có thể**

* Đối với tác vụ lặp lại (như nhận diện offline, gợi ý bàn phím...), nên **triển khai bằng Edge AI** để:

  * Giảm số lần gọi API cloud.
  * Không cần trả phí theo lượt sử dụng.

### 2. **Dùng mô hình nhẹ**

* Áp dụng các kỹ thuật như:

  * **Quantization**: rút gọn trọng số từ 32-bit xuống 8-bit.
  * **Pruning**: loại bỏ neuron không ảnh hưởng nhiều.
  * **Distillation**: mô hình nhỏ học lại từ mô hình lớn.
* Sử dụng các mô hình nhẹ sẵn có:

  * **MobileNet**, **EfficientNet**, **DistilBERT**, **TinyML models**...

### 3. **Tận dụng công cụ open-source**

* **TensorFlow Lite**, **PyTorch Mobile**, **ONNX Runtime Mobile**
* Các SDK chuyên dụng:

  * **Apple Core ML** (iOS)
  * **Google ML Kit** (Android)
  * **MediaPipe** cho xử lý ảnh/video

### 4. **Tối ưu chiến lược hybrid**

* Tùy từng chức năng: cái nào cần realtime thì chạy edge, cái nào cần hiểu sâu thì dùng cloud.
* Ví dụ:

  * Nhận diện khuôn mặt (edge) → xác minh danh tính (cloud).
  * Dịch văn bản offline (edge) → gợi ý bài học mở rộng (cloud).

---

## Kết luận

* **AI đang trở thành tiêu chuẩn trong mobile app**, từ giải trí đến y tế, giáo dục.
* **Cloud AI** phù hợp với ứng dụng cần xử lý nặng hoặc dùng mô hình lớn.
* **Edge AI** là lựa chọn kinh tế và hiệu quả cho các tác vụ realtime, nhạy cảm.
* Xu hướng tương lai: **hybrid AI**, nơi cloud và edge hỗ trợ lẫn nhau tối ưu.

---

Bạn có muốn tôi minh họa thêm bằng sơ đồ kiến trúc hệ thống hybrid AI, hoặc ví dụ triển khai bằng **TensorFlow Lite** và **ML Kit** không?

Hoặc tiếp tục với phần **\[Code Lab] Build a Pocket Learning Chatbot with Open-Source**?


## Note
- Local AI chạy trên máy từ 6 - 8 GB, chạy không cần mạng.



# 10:15 – 11:00 [Code Lab] Build a Pocket Learning Chatbot with Open-Source Tools

# 11:00 – 11:15 Q&A and Open Discussion