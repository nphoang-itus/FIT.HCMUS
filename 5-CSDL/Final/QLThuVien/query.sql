-- ## 1. Truy Vấn Đơn Giản
-- 1. Cho biết thông tin (ho, tenlot, ten, dienthoai) của các độc giả người lớn có địa chỉ ở quận 2.
SELECT * FROM NGUOILON

SELECT DG.HO, DG.TENLOT, DG.TEN, NL.DIENTHOAI
FROM NGUOILON NL
    JOIN DOCGIA DG ON DG.MA_DOCGIA = NL.MA_DOCGIA
WHERE NL.QUAN = '2';

-- 2. Cho biết mã, tên, tác giả của những tựa sách được viết bởi tác giả "Jack London".
SELECT TS.MA_TUASACH, TS.TUASACH, TS.TACGIA
FROM TUASACH TS
WHERE TS.TACGIA = 'Jack London'

-- 3. Cho biết mã cuốn sách, tình trạng của những cuốn sách có tình trạng "Y" (hư hỏng).
SELECT DISTINCT MA_CUONSACH, TINHTRANG
FROM CUONSACH
WHERE TINHTRANG = 'Y'

-- 4. Cho biết thông tin (mã, họ tên) của các độc giả đã mượn sách trong tháng 2/2014.
SELECT DISTINCT DG.MA_DOCGIA, DG.HO + ' ' + DG.TENLOT + ' ' + DG.TEN AS HOTEN
FROM DOCGIA DG
    JOIN MUON M ON M.MA_DOCGIA = DG.MA_DOCGIA
WHERE MONTH(M.NGAYGIO_MUON) = 2 AND YEAR(M.NGAYGIO_MUON) = 2014

-- 5. Cho biết mã và tên tựa sách của những sách bằng tiếng Việt.
SELECT TS.MA_TUASACH, TS.TUASACH
FROM TUASACH TS
    JOIN DAUSACH DS ON DS.MA_TUASACH = TS.MA_TUASACH
WHERE DS.NGONNGU = N'VIỆT'

-- 6. Hiển thị thông tin về các đầu sách có bìa cứng và đang trong tình trạng có thể cho mượn.
SELECT DISTINCT *
FROM DAUSACH DS
    JOIN CUONSACH CS ON CS.ISBN = DS.ISBN
WHERE DS.BIA = N'Bìa cứng' AND DS.TRANGTHAI = 'Y' AND CS.TINHTRANG = 'Y'

-- 7. Cho biết họ tên đầy đủ của các độc giả trẻ em và người lớn bảo trợ.
SELECT DG.HO + ' ' + DG.TENLOT + ' ' + DG.TEN AS HOTEN_TREEM, DGNL.HO + ' ' + DGNL.TENLOT + ' ' + DGNL.TEN AS HOTEN_NGUOILON
FROM TREEM TE
    JOIN DOCGIA DG ON DG.MA_DOCGIA = TE.MA_DOCGIA
    JOIN NGUOILON NL ON NL.MA_DOCGIA = TE.MA_DOCGIA_NGUOILON
    JOIN DOCGIA DGNL ON NL.MA_DOCGIA = DGNL.MA_DOCGIA

-- 8. Liệt kê các cuốn sách đã được mượn nhưng quá hạn trả (ngày hết hạn < ngày hiện tại).
SELECT DISTINCT TS.TUASACH, DS.NGONNGU, M.MA_CUONSACH
FROM MUON M
    JOIN DAUSACH DS ON DS.ISBN = M.ISBN
    JOIN TUASACH TS ON TS.MA_TUASACH = DS.MA_TUASACH
WHERE M.NGAY_HETHAN < GETDATE()

-- 9. Cho biết thông tin về các tựa sách và đầu sách tương ứng được xuất bản bằng tiếng Anh.
SELECT DISTINCT *
FROM DAUSACH DS
    JOIN TUASACH TS ON TS.MA_TUASACH = DS.MA_TUASACH
WHERE DS.NGONNGU = 'Anh'

-- 10. Hiển thị thông tin về những đầu sách đã được đăng ký mượn vào ngày 03/03/2012.
SELECT *
FROM DANGKY DK
    JOIN DAUSACH DS ON DS.ISBN = DK.ISBN
WHERE DK.NGAYGIO_DK = '2012/03/03'

-- 11. Liệt kê các cuốn sách có mã đầu sách '1' và tình trạng còn tốt.

-- 12. Cho biết thông tin của các độc giả sinh sau năm 2000.

-- 13. Liệt kê các đầu sách và số lượng cuốn sách tương ứng.

-- 14. Cho biết mã cuốn sách, isbn và tình trạng của các cuốn sách thuộc đầu sách có mã '10'.

-- 15. Liệt kê thông tin về các độc giả đã mượn sách của đầu sách có mã '1'.

-- ## 2. Gom Nhóm + Hàm

-- 16. Thống kê số lượng đầu sách theo từng ngôn ngữ, sắp xếp theo thứ tự giảm dần của số lượng.
SELECT DS.NGONNGU, COUNT(DS.ISBN) AS SOLUONG
FROM DAUSACH DS
GROUP BY DS.NGONNGU
ORDER BY SOLUONG DESC

-- 17. Với mỗi độc giả người lớn, cho biết số lượng trẻ em mà họ bảo trợ.
SELECT DGNL.HO + ' ' + DGNL.TENLOT + ' ' + DGNL.TEN AS HOTEN_NGUOILON, COUNT(TE.MA_DOCGIA) AS SOLUONG
FROM TREEM TE
    JOIN DOCGIA DGNL ON DGNL.MA_DOCGIA = TE.MA_DOCGIA_NGUOILON
GROUP BY DGNL.HO, DGNL.TENLOT, DGNL.TEN, TE.MA_DOCGIA_NGUOILON;

-- 18. Thống kê số lượng cuốn sách theo từng đầu sách và tình trạng của chúng.
SELECT TS.TUASACH, DS.ISBN, CS.TINHTRANG, COUNT(CS.MA_CUONSACH) AS SLCUONSACH
FROM CUONSACH CS
    JOIN DAUSACH DS ON DS.ISBN = CS.ISBN
    JOIN TUASACH TS ON TS.MA_TUASACH = DS.MA_TUASACH
GROUP BY TS.TUASACH, DS.ISBN, CS.TINHTRANG

-- 19. Đếm số lượng sách được mượn trong từng tháng của năm 2014, sắp xếp theo thứ tự tăng dần của tháng.
SELECT MONTH(NGAYGIO_MUON) AS THANG, COUNT(MA_CUONSACH) AS SLCUONSACH
FROM MUON
GROUP BY MONTH(NGAYGIO_MUON)
ORDER BY THANG ASC

-- 20. Cho biết tổng số tiền mượn đã thu được trong năm 2013.

-- 21. Tính số ngày trung bình mà độc giả giữ sách trước khi trả (từ ngày mượn đến ngày trả).
SELECT DG.TEN, AVG(DATEDIFF(D, M.NGAYGIO_MUON, M.NGAYGIO_TRA)) AS NGAYTRUNGBINH
FROM DOCGIA DG
    JOIN QUATRINHMUON M ON M.MA_DOCGIA = DG.MA_DOCGIA
GROUP BY DG.TEN, DG.MA_DOCGIA

-- 22. Thống kê số lượng đầu sách theo từng loại bìa.
SELECT BIA, COUNT(ISBN) AS SLDAUSACH
FROM DAUSACH
GROUP BY BIA

-- 23. Tính tổng số tiền đặt cọc theo từng quận của độc giả.

-- 24. Tìm mã độc giả đã mượn nhiều sách nhất và số lượng sách họ đã mượn.
SELECT DISTINCT M.MA_DOCGIA, COUNT(DISTINCT M.MA_CUONSACH) AS SLSACHMUON
FROM MUON M
GROUP BY M.MA_DOCGIA
HAVING COUNT(DISTINCT M.MA_CUONSACH) >= ALL (
    SELECT COUNT(DISTINCT M1.MA_CUONSACH)
    FROM MUON M1
    GROUP BY M1.MA_DOCGIA
)

-- 25. Thống kê số lượng độc giả theo từng quận, sắp xếp theo thứ tự giảm dần.
SELECT NL.QUAN, COUNT(DG.MA_DOCGIA) AS SOLUONGDOCGIA
FROM DOCGIA DG
    LEFT JOIN NGUOILON NL ON DG.MA_DOCGIA = NL.MA_DOCGIA
    LEFT JOIN TREEM TE ON DG.MA_DOCGIA = TE.MA_DOCGIA
    LEFT JOIN NGUOILON TENL ON TENL.MA_DOCGIA = TE.MA_DOCGIA_NGUOILON
GROUP BY NL.QUAN, TENL.QUAN
ORDER BY NL.QUAN DESC

-- 25. Thống kê số lượng độc giả theo từng quận, sắp xếp theo thứ tự giảm dần. (HAY)
SELECT 
    NL.QUAN,
    COUNT(DISTINCT DG.MA_DOCGIA) + COUNT(DISTINCT TE.MA_DOCGIA) AS TONG_DOCGIA
FROM NGUOILON NL
    JOIN DOCGIA DG ON DG.MA_DOCGIA = NL.MA_DOCGIA
    LEFT JOIN TREEM TE ON TE.MA_DOCGIA_NGUOILON = NL.MA_DOCGIA
GROUP BY NL.QUAN
ORDER BY TONG_DOCGIA DESC;

-- 26. Tính trung bình số ngày mượn sách của từng độc giả.
SELECT QT.MA_DOCGIA, AVG(DATEDIFF(D, QT.NGAYGIO_MUON, QT.NGAYGIO_TRA)) AS TRUNGBINHNGAYMUON
FROM QUATRINHMUON QT
GROUP BY QT.MA_DOCGIA

-- -- 27. Cho biết số lượng sách được mượn bởi độc giả ở từng quận.
-- SELECT NL.QUAN, COUNT(DISTINCT M.ISBN, M.MA_CUONSACH) AS SOLUONGSACH
-- FROM MUON M
--     JOIN NGUOILON NL ON NL.MA_DOCGIA = M.MA_DOCGIA
--     LEFT JOIN (
--         SELECT T.MA_DOCGIA, T.MA_DOCGIA_NGUOILON
--         FROM MUON M2 JOIN TREEM T ON T.MA_DOCGIA = M2.MA_DOCGIA
--     ) TREEM_MUON ON TREEM_MUON.MA_DOCGIA_NGUOILON = NL.MA_DOCGIA
-- GROUP BY NL.QUAN

-- -- SELECT * FROM MUON
-- -- SELECT * FROM TREEM
-- -- SELECT * FROM NGUOILON

-- 28. Thống kê số lượng sách theo từng tác giả, sắp xếp theo thứ tự giảm dần.


-- 29. Tìm tựa sách được mượn nhiều nhất trong năm 2013.

-- 30. Cho biết tỷ lệ sách bị hư hỏng (tình trạng 'Y') trên tổng số sách.

-- ## 3. Truy Vấn Lồng + Hàm

-- 31. Tìm độc giả đã mượn ít nhất 3 đầu sách khác nhau.
SELECT M.MA_DOCGIA
FROM MUON M
GROUP BY M.MA_DOCGIA
HAVING COUNT(M.ISBN) >= 3

-- 32. Tìm tựa sách chưa từng được mượn.
SELECT TS.MA_TUASACH, TS.TUASACH
FROM TUASACH TS
WHERE NOT EXISTS (
    SELECT 1
    FROM MUON M JOIN DAUSACH DS ON DS.ISBN = M.ISBN
    WHERE DS.MA_TUASACH = TS.MA_TUASACH
)

-- 33. Tìm độc giả có số lần mượn sách nhiều nhất.
SELECT M.MA_DOCGIA
FROM MUON M
GROUP BY M.MA_DOCGIA
HAVING COUNT(*) >= ALL (
    SELECT COUNT(*)
    FROM MUON M2
    GROUP BY M2.MA_DOCGIA
)

-- 34. Cho biết thông tin về đầu sách có nhiều cuốn sách bị hư hỏng nhất.
SELECT DS.ISBN, DS.MA_TUASACH, DS.NGONNGU
FROM CUONSACH CS JOIN DAUSACH DS ON DS.ISBN = CS.ISBN
WHERE CS.TINHTRANG = 'N'
GROUP BY DS.ISBN, DS.MA_TUASACH, DS.NGONNGU
HAVING COUNT(CS.MA_CUONSACH) >= ALL (
    SELECT COUNT(CS2.MA_CUONSACH)
    FROM CUONSACH CS2
    WHERE CS2.TINHTRANG = 'N'
    GROUP BY CS2.ISBN
)

-- 35. Tìm độc giả đã mượn tất cả các đầu sách của tác giả "Jack London".
SELECT DG.MA_DOCGIA, DG.TEN
FROM DOCGIA DG
WHERE NOT EXISTS (
    SELECT DS.ISBN
    FROM DAUSACH DS
        JOIN TUASACH TS ON TS.MA_TUASACH = DS.MA_TUASACH
    WHERE TS.TACGIA = 'Jack London'
    
    EXCEPT

    SELECT M.ISBN
    FROM MUON M
    WHERE M.MA_DOCGIA = DG.MA_DOCGIA
)

-- 36. Hiển thị thông tin của độc giả có tổng thời gian mượn sách dài nhất.
SELECT DG.MA_DOCGIA, DG.TEN
FROM QUATRINHMUON QTM
    JOIN MUON M ON QTM.ISBN = M.ISBN AND QTM.MA_CUONSACH = M.MA_CUONSACH
    JOIN DOCGIA DG ON DG.MA_DOCGIA = M.MA_DOCGIA
GROUP BY DG.MA_DOCGIA, DG.TEN
HAVING SUM(DATEDIFF(D, QTM.ngayGio_muon, QTM.ngayGio_tra)) >= ALL (
    SELECT SUM(DATEDIFF(D, Q2.ngayGio_muon, Q2.ngayGio_tra))
    FROM QUATRINHMUON Q2
        JOIN MUON M2 ON Q2.ISBN = M2.ISBN AND Q2.MA_CUONSACH = M2.MA_CUONSACH
    GROUP BY M2.MA_DOCGIA
);

-- 37. Tìm các đầu sách được mượn bởi ít nhất 2 độc giả khác nhau.
SELECT M.ISBN
FROM MUON M
GROUP BY M.ISBN
HAVING COUNT(DISTINCT M.MA_DOCGIA) >= 2;

-- 38. Cho biết cuốn sách được mượn nhiều lần nhất.
SELECT M.ISBN, M.MA_CUONSACH
FROM MUON M
GROUP BY M.ISBN, M.MA_CUONSACH
HAVING COUNT(M.ma_docgia) >= ALL (
    SELECT COUNT(M2.ma_docgia)
    FROM MUON M2
    GROUP BY M2.ISBN, M2.MA_CUONSACH
)

-- 39. Tìm tất cả các cặp độc giả đã từng mượn cùng một đầu sách.
SELECT DISTINCT M1.MA_DOCGIA, M2.MA_DOCGIA
FROM MUON M1
    JOIN MUON M2 ON M2.ISBN = M1.ISBN AND M2.MA_CUONSACH = M1.MA_CUONSACH
WHERE M1.MA_DOCGIA != M2.MA_DOCGIA

-- 40. Liệt kê các độc giả đã mượn sách nhưng chưa bao giờ trả muộn.
SELECT DISTINCT DG.MA_DOCGIA
FROM DOCGIA DG
    JOIN MUON M1 ON M1.ma_docgia = DG.ma_docgia
WHERE NOT EXISTS (
    SELECT 1
    FROM MUON M
        JOIN QuaTrinhMuon QTM
            ON QTM.isbn = M.ISBN
            AND QTM.ma_cuonsach = M.ma_cuonsach
            AND M.ngayGio_muon = QTM.ngayGio_muon
            AND M.ngay_hethan = QTM.ngay_hethan
            AND M.ma_docgia = QTM.ma_docgia
    WHERE QTM.ngayGio_tra > M.ngay_hethan AND M.ma_docgia = DG.ma_docgia
)

-- 41. Tìm đầu sách có tỷ lệ đăng ký mượn cao nhất so với số lượng cuốn sách thực tế.

-- 42. Liệt kê các độc giả có lịch sử mượn sách tương tự nhau (mượn ít nhất 2 đầu sách giống nhau).
SELECT DG.ma_docgia, DG.ten
FROM DOCGIA DG
    JOIN QUATRINHMUON QT ON QT.ma_docgia = DG.ma_docgia
GROUP BY DG.ma_docgia, DG.TEN, QT.ISBN, QT.MA_CUONSACH
HAVING COUNT(QT.ngayGio_muon) >= 2

-- 43. Tìm cuốn sách được mượn và trả đúng hạn nhiều lần nhất.
SELECT QT.ISBN, QT.MA_CUONSACH
FROM QUATRINHMUON QT
WHERE QT.ngayGio_tra <= QT.ngay_hethan
GROUP BY QT.ISBN, QT.MA_CUONSACH
HAVING COUNT(QT.ngayGio_muon) >= ALL (
    SELECT COUNT(QT2.ngayGio_muon)
    FROM QUATRINHMUON QT2
    WHERE QT2.ngayGio_tra <= QT2.ngay_hethan
    GROUP BY QT2.ISBN, QT2.MA_CUONSACH
)

-- ## 4. Phép Chia

-- 44. Tìm những độc giả đã mượn tất cả các đầu sách bằng tiếng Việt.
SELECT DG1.ma_docgia, DG1.ten
FROM DOCGIA DG1
WHERE NOT EXISTS (
    SELECT DS1.ISBN
    FROM DAUSACH DS1
    WHERE DS1.NGONNGU = N'Việt'

    EXCEPT

    SELECT QT2.ISBN
    FROM QUATRINHMUON QT2
    WHERE QT2.ma_docgia = DG1.ma_docgia
)

-- 45. Tìm độc giả đã mượn tất cả các đầu sách của tác giả "Chu Lai".
SELECT DG.ma_docgia, DG.ten
FROM DOCGIA DG
WHERE NOT EXISTS (
    SELECT DS.ISBN
    FROM DAUSACH DS JOIN TUASACH TS ON TS.ma_tuasach = DS.ma_tuasach
    WHERE TS.TACGIA = 'Chu Lai'

    EXCEPT

    SELECT QT.ISBN
    FROM QUATRINHMUON QT
    WHERE QT.MA_DOCGIA = DG.ma_docgia
)

-- 46. Tìm những độc giả trẻ em đã mượn tất cả các đầu sách tiếng Anh.
SELECT TE.ma_docgia
FROM TREEM TE
WHERE NOT EXISTS (
    SELECT DS.ISBN
    FROM DAUSACH DS
    WHERE DS.NGONNGU = 'Anh'
    
    EXCEPT
    
    SELECT QT.ISBN
    FROM QUATRINHMUON QT
    WHERE QT.ma_docgia = TE.ma_docgia
)

-- 47. Tìm quận nào có độc giả đã mượn tất cả các loại ngôn ngữ sách.
SELECT DISTINCT NL.quan
FROM NGUOILON NL
WHERE NOT EXISTS (
    SELECT DS.NGONNGU
    FROM DAUSACH DS

    EXCEPT

    SELECT DS2.ngonngu
    FROM QUATRINHMUON QT
        JOIN DauSach DS2 ON DS2.ISBN = QT.ISBN
        JOIN DOCGIA DG ON DG.ma_docgia = QT.ma_docgia
        LEFT JOIN NGUOILON NL2 ON NL2.ma_docgia = DG.ma_docgia
        LEFT JOIN TREEM TE ON TE.ma_docgia = DG.ma_docgia
        LEFT JOIN NGUOILON NLTE ON NLTE.ma_docgia = TE.ma_docgia_nguoilon
    WHERE NL2.quan = NL.quan OR NLTE.quan = NL.quan
)

-- 48. Cho biết những độc giả đã mượn tất cả các đầu sách được xuất bản bằng bìa cứng.
SELECT DISTINCT DG.ma_docgia, DG.ten
FROM DOCGIA DG
WHERE NOT EXISTS (
    SELECT DS.ISBN
    FROM DAUSACH DS
    WHERE DS.BIA = N'Bìa cứng'

    EXCEPT

    SELECT QT.ISBN
    FROM QUATRINHMUON QT
    WHERE QT.MA_DOCGIA = DG.ma_docgia
)

-- 49. Tìm những tác giả có tất cả các tựa sách của họ đều đã được mượn ít nhất một lần.
SELECT DISTINCT tacgia
FROM TUASACH TS
WHERE NOT EXISTS (
    -- Tựa sách của tác giả này chưa được mượn
    SELECT 1
    FROM TUASACH TS2
    WHERE TS2.tacgia = TS.tacgia
    AND NOT EXISTS (
        SELECT 1
        FROM QUATRINHMUON QT
        JOIN DAUSACH DS ON DS.ISBN = QT.ISBN
        WHERE DS.ma_tuasach = TS2.ma_tuasach
    )
)
ORDER BY tacgia;

-- 50. Tìm những độc giả đã mượn tất cả các đầu sách có mã tuasach từ 1 đến 5.
SELECT DG.ma_docgia, DG.ten
FROM DOCGIA DG
WHERE NOT EXISTS (
    SELECT 1
    FROM DAUSACH DS
    WHERE (DS.ma_tuasach BETWEEN '1' AND '5')
    AND NOT EXISTS (
        SELECT 1
        FROM QuaTrinhMuon QT JOIN DAUSACH DS2 ON DS2.isbn = QT.isbn
        WHERE QT.ma_docgia = DG.ma_docgia AND DS2.ISBN = DS.ISBN
    )
)
-- ## 1. Truy Vấn với MAX/MIN và Subquery

-- 1. Cho biết thông tin đầu sách có số lượng cuốn sách nhiều nhất.
SELECT DISTINCT CS.ISBN
FROM CUONSACH CS
GROUP BY CS.ISBN
HAVING COUNT(CS.Ma_CuonSach) >= ALL (
    SELECT COUNT(CS2.Ma_CuonSach)
    FROM CUONSACH CS2
    GROUP BY CS2.ISBN
)

-- 2. Tìm độc giả có tuổi lớn nhất trong từng quận.
SELECT DG.ma_docgia, DG.ten, NL.quan, YEAR(GETDATE()) - YEAR(DG.NgaySinh) AS TUOI
FROM DocGia DG JOIN NguoiLon NL ON NL.ma_docgia = DG.ma_docgia
WHERE YEAR(GETDATE()) - YEAR(DG.NgaySinh) >= ALL (
    SELECT YEAR(GETDATE()) - YEAR(DG2.NgaySinh)
    FROM DocGia DG2 JOIN NguoiLon NL2 ON NL2.ma_docgia = DG2.ma_docgia
    WHERE NL2.quan = NL.quan
)

-- 3. Cho biết tựa sách có tổng số lần mượn nhiều nhất.
SELECT TS.ma_tuasach, TS.TuaSach, TS.tacgia
FROM QUATRINHMUON QT
    JOIN DAUSACH DS ON QT.ISBN = DS.ISBN
    JOIN TUASACH TS ON DS.ma_tuasach = TS.ma_tuasach
GROUP BY TS.ma_tuasach, TS.TuaSach, TS.tacgia
HAVING COUNT(QT.ISBN) >= ALL (
    SELECT COUNT(QT2.ISBN)
    FROM QUATRINHMUON QT2
        JOIN DAUSACH DS2 ON QT2.ISBN = DS2.ISBN
    GROUP BY DS2.ma_tuasach
)

-- 4. Tìm quận có số lượng độc giả người lớn ít nhất.
SELECT NL1.quan, COUNT(NL1.ma_docgia)
FROM NguoiLon NL1
GROUP BY NL1.QUAN
HAVING COUNT(NL1.ma_docgia) <= ALL (
    SELECT COUNT(NL2.ma_docgia)
    FROM NguoiLon NL2
    GROUP BY NL2.quan
)

-- 5. Cho biết đầu sách có tỷ lệ sách hư hỏng cao nhất.
SELECT CS.isbn
FROM CUONSACH CS
WHERE CS.TinhTrang = 'N'
GROUP BY CS.ISBN
HAVING COUNT(CS.MA_CUONSACH) >= ALL (
    SELECT COUNT(CS2.MA_CUONSACH)
    FROM CUONSACH CS2
    WHERE CS2.TinhTrang = 'N'
    GROUP BY CS2.isbn
)

-- ## 2. Truy Vấn với ALL/ANY

-- 6. Tìm độc giả có số lần mượn sách nhiều hơn tất cả độc giả ở quận 'TD'.
SELECT DG.ma_docgia, DG.ten
FROM DOCGIA DG
    JOIN QuaTrinhMuon QT ON QT.ma_docgia = DG.ma_docgia
GROUP BY DG.ma_docgia, DG.ten
HAVING COUNT(QT.MA_CUONSACH) >= ALL (
    SELECT COUNT(QT2.MA_CUONSACH)
    FROM QuaTrinhMuon QT2
        JOIN DocGia DG2 ON DG2.ma_docgia = QT2.ma_docgia
        LEFT JOIN NGUOILON NL ON NL.ma_docgia = DG2.ma_docgia
        LEFT JOIN TREEM TE ON DG2.ma_docgia = TE.ma_docgia
        LEFT JOIN NGUOILON BT ON BT.ma_docgia = TE.ma_docgia_nguoilon
    WHERE NL.QUAN = 'TD' OR BT.quan = 'TD'
    GROUP BY QT2.ma_docgia
)

-- 7. Cho biết tựa sách có số lượng cuốn sách ít hơn bất kỳ tựa sách nào của tác giả 'Jack London'.
SELECT TS.ma_tuasach, TS.TuaSach, COUNT(CS.Ma_CuonSach) AS SLCUONSACH
FROM DAUSACH DS
    JOIN CUONSACH CS ON CS.ISBN = DS.ISBN
    JOIN TUASACH TS ON TS.ma_tuasach = DS.ma_tuasach
WHERE TS.tacgia != 'Jack London'
GROUP BY TS.ma_tuasach, TS.TuaSach
HAVING COUNT(CS.Ma_CuonSach) < ANY (
    SELECT COUNT(CS2.MA_CUONSACH)
    FROM CUONSACH CS2
        JOIN DAUSACH DS2 ON DS2.ISBN = CS2.ISBN
        JOIN TUASACH TS2 ON TS2.ma_tuasach = DS2.ma_tuasach
    WHERE TS2.TACGIA = 'Jack London'
    GROUP BY TS2.ma_tuasach
)

-- 8. Tìm độc giả trẻ em có tuổi lớn hơn tất cả độc giả trẻ em có người bảo trợ ở quận '2'.
SELECT DG.ma_docgia, DG.ten, YEAR(GETDATE()) - YEAR(DG.NGAYSINH) AS TUOI
FROM TREEM TE
    JOIN DOCGIA DG ON TE.ma_docgia = DG.ma_docgia
WHERE YEAR(GETDATE()) - YEAR(DG.NGAYSINH) >= ALL (
    SELECT YEAR(GETDATE()) - YEAR(DG2.NGAYSINH)
    FROM TREEM TE2
        JOIN DOCGIA DG2 ON TE2.ma_docgia = DG2.ma_docgia
        JOIN NGUOILON BT ON BT.ma_docgia = TE2.ma_docgia_nguoilon
    WHERE BT.QUAN = '2'
)

-- 9. Cho biết đầu sách có thời gian mượn trung bình dài hơn bất kỳ đầu sách tiếng Anh nào.
SELECT distinct qt.isbn, AVG(DATEDIFF(D, QT.ngayGio_muon, QT.ngayGio_tra)) as tbtgmuon
FROM QUATRINHMUON QT
GROUP BY qt.isbn
HAVING AVG(DATEDIFF(D, QT.ngayGio_muon, QT.ngayGio_tra)) > ANY (
    SELECT AVG(DATEDIFF(D, QT2.ngayGio_muon, QT2.ngayGio_tra))
    FROM QuaTrinhMuon QT2
        JOIN DAUSACH DS ON DS.ISBN = QT2.isbn
    WHERE DS.ngonngu = 'Anh'
    GROUP BY DS.isbn
)

-- 10. Tìm những cuốn sách chưa bao giờ được mượn trong khi tất cả cuốn sách khác của cùng đầu sách đã được mượn.
SELECT CS.ISBN, CS.Ma_CuonSach
FROM CUONSACH CS
WHERE 
    -- Điều kiện 1: Cuốn sách này chưa bao giờ được mượn
    NOT EXISTS (
        SELECT 1
        FROM QUATRINHMUON QT
        WHERE QT.ISBN = CS.ISBN AND QT.MA_CUONSACH = CS.Ma_CuonSach
    )
    -- Điều kiện 2: Có ít nhất 1 cuốn sách khác thuộc đầu sách này
    AND EXISTS (
        SELECT 1
        FROM CUONSACH CS2
        WHERE CS2.ISBN = CS.ISBN AND CS2.Ma_CuonSach != CS.Ma_CuonSach
    )
    -- Điều kiện 3: Tất cả các cuốn sách khác của cùng đầu sách đều đã được mượn
    AND NOT EXISTS (
        SELECT 1
        FROM CUONSACH CS3
        WHERE CS3.ISBN = CS.ISBN 
          AND CS3.Ma_CuonSach != CS.Ma_CuonSach
          AND NOT EXISTS (
              SELECT 1
              FROM QUATRINHMUON QT2
              WHERE QT2.ISBN = CS3.ISBN AND QT2.MA_CUONSACH = CS3.Ma_CuonSach
          )
    )


-- ## 3. Truy Vấn với EXISTS/NOT EXISTS

-- 11. Cho biết tên độc giả chưa từng mượn sách nào.

-- 12. Tìm những tựa sách mà không có đầu sách nào bằng tiếng Việt.

-- 13. Cho biết những độc giả đã mượn sách nhưng chưa bao giờ trả muộn.

-- 14. Tìm những đầu sách có ít nhất một cuốn sách bị hư hỏng.

-- 15. Cho biết những độc giả người lớn không có trẻ em nào được bảo trợ.

-- 16. Tìm những tác giả có ít nhất một tựa sách chưa từng được mượn.

-- 17. Cho biết những quận có độc giả đã mượn sách trong tháng 3/2014.

-- 18. Tìm những độc giả đã đăng ký mượn sách nhưng chưa thực sự mượn.

-- 19. Cho biết những đầu sách được mượn bởi cả độc giả người lớn và trẻ em.

-- 20. Tìm những tựa sách có tất cả đầu sách đều trong tình trạng hoạt động.

-- ## 4. Phép Chia (Relational Division) - Cách 1: NOT EXISTS

-- 21. Tìm độc giả đã mượn tất cả các đầu sách của tác giả 'Jack London'.

-- 22. Cho biết những độc giả đã mượn tất cả các đầu sách bằng tiếng Việt.

-- 23. Tìm những quận có độc giả đã mượn tất cả các loại ngôn ngữ sách.

-- 24. Cho biết độc giả nào đã mượn tất cả các đầu sách có bìa cứng.

-- 25. Tìm những độc giả đã mượn tất cả các đầu sách của tựa sách 'Last of the Mohicans'.

-- ## 5. Phép Chia - Cách 2: GROUP BY và HAVING

-- 26. Tìm độc giả đã mượn tất cả các đầu sách của tác giả 'Chu Lai' (dùng GROUP BY).

-- 27. Cho biết những độc giả đã mượn tất cả các đầu sách tiếng Anh (dùng HAVING).

-- 28. Tìm những quận có độc giả mượn đủ tất cả loại bìa sách (cứng và mềm).

-- 29. Cho biết độc giả nào đã mượn tất cả các cuốn sách của đầu sách có isbn = '1'.

-- 30. Tìm những độc giả đã trải qua tất cả các quá trình mượn trả của một cuốn sách cụ thể.

-- ## 6. Phép Chia - Cách 3: EXCEPT

-- 31. Tìm độc giả đã mượn tất cả các đầu sách của tác giả 'Đoàn Giỏi' (dùng EXCEPT).

-- 32. Cho biết những độc giả đã mượn tất cả các đầu sách tiếng Nhật (dùng EXCEPT).

-- 33. Tìm những độc giả trẻ em đã mượn tất cả các đầu sách mà người bảo trợ từng mượn.

-- 34. Cho biết những quận có độc giả đã mượn tất cả các tựa sách xuất bản năm 2013.

-- 35. Tìm những độc giả đã mượn tất cả các đầu sách được đăng ký trong ngày 03/03/2012.

-- ## 7. Truy Vấn Phức Tạp Kết Hợp

-- 36. Cho biết độc giả nào đã mượn nhiều sách nhất trong số những người đã mượn tất cả đầu sách tiếng Pháp.

-- 37. Tìm tác giả có tổng số lượt mượn cao nhất trong số những tác giả có ít nhất 2 tựa sách.

-- 38. Cho biết quận có tỷ lệ trả sách đúng hạn cao nhất trong số các quận có trên 3 độc giả.

-- 39. Tìm những độc giả có thời gian mượn sách trung bình dài nhất trong số những người đã mượn ít nhất 5 lần.

-- 40. Cho biết đầu sách được mượn nhiều nhất trong số những đầu sách chưa có cuốn nào bị hư hỏng.

-- ## 8. Truy Vấn Nâng Cao với Multiple Conditions

-- 41. Tìm những độc giả đã mượn sách của tất cả tác giả có tên chứa từ 'Nguyễn'.

-- 42. Cho biết những tháng có tất cả các đầu sách tiếng Việt đều được mượn ít nhất một lần.

-- 43. Tìm những độc giả đã mượn tất cả các đầu sách được xuất bản trong năm có nhiều đầu sách nhất.

-- 44. Cho biết những quận có độc giả đã mượn tất cả các loại sách (theo ngôn ngữ) có trong thư viện.

-- 45. Tìm những độc giả đã trả đúng hạn tất cả các lần mượn sách trong năm 2013.