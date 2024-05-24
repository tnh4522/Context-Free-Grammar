Chương Trình Mô Tả Một Văn Phạm Phân Tích Cú Pháp Sử Dụng Phương Pháp Tiên Đoán
Trình Tự Hoạt Động:
    1.Lớp CFG: Khởi tạo Văn Phạm từ file CSV
        +) Trong file CSV:
            Mỗi hàng là một sản xuất A -> α, với ô đầu tiên là A, các ô kế là α
        +) Cấu trúc dữ liệu CFG.h:
            + Ký hiệu bắt đầu s
            + Tập ký hiệu kết thúc Σ
            + Tập ký hiệu chưa kết thúc Δ
            + Tập các sản xuất Prod:
                - Lớp Prod.h:
                    + Ký hiệu A
                    + Danh sách alpha
        +) Đọc dữ liệu:
            + Hàm dựng CFG với tham số là đường dẫn tới file CSV
            + Trong hàm dựng:
                - Đọc từng hàng 1 -> tạo Prod để lấy dữ liệu hàng -> thêm vào Tập Prod
                - Ô đầu tiên của hàng đầu tiên trong file CSV là ký hiệu bắt đầu s
                - Từ Tập Prod:
                    Với mỗi Prod.A, thêm vào Tập Δ
                    Với mỗi Prod.alpha:
                        Sử dụng hàm CFG.getToken() để tách alpha thành các ký hiệu độc lập -> thêm các ký hiệu vào tập Σ
                        Lọc các ký hiệu ∈ Δ trong Σ, được tập Σ chuẩn
    2.Lớp M: Nhận dữ liệu văn phạm từ CFG để tạo bảng tiên đoán
        +) Cấu trúc dữ liệu:
            + Tập tiên đoán RCP(Row-Column-Prod), tương đương tập M[A, α]:
                - Lớp RCP.h:
                    Prod
                    Pair
                        - Lớp Pair.h:
                            Cặp key-value tương đương tên hàng & cột
            + Tập ký hiệu kết thúc Σ
            + Tập ký hiệu chưa kết thúc Δ
            + Tập các sản xuất Prod
        +) Khởi tạo: 
            + Hàm dựng nhận tập đầu vào Σ, Δ, Prod từ CFG
            + Quét qua tập Prod, với mỗi A -> α trong Prod:
                Nếu α là ε, tính First(A):
                    Tạo list output, bắt đầu đệ quy M.FirstLoop(X);
                    - B1: Với tham số là xâu X, lấy A là ký hiệu đầu tiên trong X
                    - B2: Nếu A ∈ Σ hoặc là ε -> return output += A
                          Nếu A ∈ Δ, tìm Prod có chứa A:
                            Tương ứng với mỗi α trong Prod.α, M.FirstLoop(α)
                Nếu α khác ε, tính Follow(α):
                    Tạo danh sách lưu vết tracer, kết quả output, gọi M.FollowTemp():
                        M.FollowTemp(α, tracer):
                            Nếu tracer.exist(α), trả về output
                            Nếu chưa quét, đệ quy M.FindFollow(α, tracer):
                                B1: tracer.add(α)
                                B2: Nếu α là CFG.s, output.add(α)
                                    Nếu α khác CFG.s:
                                        Lấy ra các Prod có chứa α
                                        Tương ứng với mỗi α trong Prod.α, lấy ký hiệu temp bên phải α:
                                            Nếu temp == ε -> output += M.FollowTemp(temp, tracer);
                                            Nếu temp != ε: 
                                                Nếu temp ∈ Σ -> output.add(temp);
                                                Nếu temp ∉ Σ -> tính First(temp), quét từng ký hiệu temp1 trong First(temp):
                                                    Nếu temp1 = ε -> output.add(M.FollowTemp(temp1, tracer))
                                                    Nếu temp1 != ε -> output.add(temp1)
                                B3: return output
                Trong tập First(A) hoặc Follow(α) nhận được:
                    Với mỗi ký hiệu Z trong tập:
                        Tạo Pair: Key = A, Value = Z
                        Tạo Prod: Prod.A = A, Prod.α = α
                        Tạo RCP(Pair, Prod), thêm vào tập RCP, được tập tiên đoán, từ tập tiên đoán có bảng tiên đoán
    3. Sử dụng hàm trong CFG để thực hiện thuật toán ở dạng view:
        - In Văn Phạm CFG
        - In xâu X, với xâu X lấy từ tham số trong hàm
        - In bảng tiên đoán M
        - Thực hiện thuật toán:
            Bắt đầu: Khởi tạo một STACK = CFG.s, BUFFER = X;
            Vòng Lặp: Nếu STACK.isEmpty() & BUFFER isEmpty() -> Dừng vòng lặp, trả về true
                      Nếu ký hiệu a ∈ Σ ở đỉnh STACK và đầu BUFFER -> STACK.POP() & BUFFER.DelHead()
                      Nếu ký hiệu a ∈ Σ ở đỉnh STACK & a ∈ Δ ở đỉnh BUFFER -> lấy Prod = M[A, α], STACK.POP(), STACK.Push(Prod.A)
                      Nếu !STACK.isEmpty() & BUFFER isEmpty(), hoặc ngược lại -> Dừng vòng lặp, trả về False;
            Với mỗi điều kiện, xuất ra số lần lặp, STACK, BUFFER hiện tại & kết hành động ứng

Cấu trúc chương trình:
    + Cấu trúc dữ liệu CFG:
        + Đọc & Xuất CFG
        + Cấu trúc dữ liệu Prod
    + Cấu trúc dữ liệu M:
        + Đọc & Xuất M
        + Cấu trúc dữ liệu RCP:
            Cấu trúc dữ liệu Pair
    + StackTemplate & M.Fisrt() & các phương thức cần thiết 
    + LinkedListTemplate + M.Follow() & các phương thức cần thiết
    + CFG.checkSyntaxUsePredict() & còn lại