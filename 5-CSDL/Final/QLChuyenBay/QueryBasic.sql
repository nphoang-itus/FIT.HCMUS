-- Cho biết mã số, tên phi công, địa chỉ, điện thoại của các phi công đã từng lái máy bay loại B747.
SELECT NV.MANV, NV.TEN, NV.DCHI, NV.DTHOAI
FROM NHANVIEN NV
    JOIN PHANCONG PC ON PC.MANV = NV.MANV
    JOIN LICHBAY LB ON LB.MACB = PC.MACB
WHERE LB.MALOAI = 'B747';

-- 2. Cho biết mã số và ngày đi của các chuyến bay xuất phát từ sân bay DCA trong khoảng thời gian từ 14 giờ đến 18 giờ.
SELECT LB.MACB, LB.NGAYDI
FROM LICHBAY LB
    JOIN CHUYENBAY CB ON CB.MACB = LB.MACB
WHERE CB.SBDI = 'DCA' AND CB.GIODI BETWEEN '14:00' AND '18:00';

-- 3. Cho biết tên những nhân viên được phân công trên chuyến bay có mã số 100 xuất phát tại sân bay SLC. Các dòng dữ liệu xuất ra không được phép trùng lắp.
SELECT DISTINCT NV.TEN
FROM NHANVIEN NV
    JOIN PHANCONG PC ON PC.MANV = NV.MANV
    JOIN CHUYENBAY CB ON CB.MACB = PC.MACB
WHERE 


-- 4. Cho biết mã loại và số hiệu máy bay đã từng xuất phát tại sân bay MIA.
-- Các dòng dữ liệu xuất ra không được phép trùng lắp.
-- 5. Cho biết mã chuyến bay, ngày đi, cùng với tên, địa chỉ, điện thoại của
-- tất cả các hành khách đi trên chuyến bay đó. Sắp xếp theo thứ tự tăng
-- dần của mã chuyến bay và theo ngày đi giảm dần.
-- 6. 7. 8. 9. 10. 11. 12. 13. 14. 15. 16. Cho biết mã chuyến bay, ngày đi, cùng với tên, địa chỉ, điện thoại của
-- tất cả những nhân viên được phân công trong chuyến bay đó. Sắp xếp
-- theo thứ tự tăng dần của mã chuyến bay và theo ngày đi giảm dần.
-- Cho biết mã chuyến bay, ngày đi, mã số và tên của những phi công
-- được phân công vào chuyến bay hạ cánh xuống sân bay ORD.
-- Cho biết các chuyến bay (mã số chuyến bay, ngày đi và tên của phi
-- công) trong đó phi công có mã 1001 được phân công lái.
-- Cho biết thông tin (mã chuyến bay, sân bay đi, giờ đi, giờ đến,
-- ngày đi) của những chuyến bay hạ cánh xuống DEN. Các chuyến bay
-- được liệt kê theo ngày đi giảm dần và sân bay xuất phát (SBDI) tăng
-- dần .
-- Với mỗi phi công, cho biết hãng sản xuất và mã loại máy bay mà phi
-- công này có khả năng bay được. Xuất ra tên phi công, hãng sản xuất
-- và mã loại máy bay.
-- Cho biết mã phi công, tên phi công đã lái máy bay trong chuyến bay
-- mã số 100 vào ngày 11/01/2000.
-- Cho biết mã chuyến bay, mã nhân viên, tên nhân viên được phân công
-- vào chuyến bay xuất phát ngày 10/31/2000 tại sân bay MIA vào lúc
-- 20:30
-- Cho biết thông tin về chuyến bay (mã chuyến bay, số hiệu, mã loại,
-- hãng sản xuất) mà phi công "Quang" đã lái.
-- Cho biết tên của những phi công chưa được phân công lái chuyến bay
-- nào.
-- Cho biết tên khách hàng đã đi chuyến bay trên máy bay của hãng
-- "Boeing"
-- Cho biết mã các chuyến bay chỉ bay với máy bay số hiệu 10 và mã loại
-- B747.