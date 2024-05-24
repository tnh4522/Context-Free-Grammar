#ifndef _PPT_
#define _PPT

#include "RCP.h"
#include "Pair.h"

class M
{
private:
  void FirstLoop(string, LinkedList<string> &);
  LinkedList<string> FollowTemp(string, LinkedList<string> &);
  LinkedList<string> FindFollow(string, LinkedList<string> &);

public:
  LinkedList<RCP> data;
  LinkedList<Prod> list_prod;
  LinkedList<string> list_sigma;
  LinkedList<string> list_delta;

  void viewProcess();
  void PrintTable() const;
  void PrintListRCP() const;

  LinkedList<string> First(string);
  LinkedList<string> Follow(string);
  LinkedList<Prod> getProdContainA(string);

  Prod getProd(string) const;
  Prod operator()(const string &, const string &) const;

  string getNextA(string, const Prod &);

  friend ostream &operator<<(ostream &, const M &);

  M(const LinkedList<Prod> &, const LinkedList<string> &, const LinkedList<string> &);
  ~M();
};

void M::viewProcess()
{
  for (Node<Prod> *p = this->list_prod.head; p != NULL; p = p->next)
  {
    for (Node<string> *k = p->data.alpha.head; k != NULL; k = k->next)
    {
      cout << "Xet " << p->data.A << " -> " << k->data << endl;
      LinkedList<string> temp;
      if (k->data == "ε")
      {
        temp = this->Follow(p->data.A);
        cout << "\tCo follow(" << p->data.A;
      }
      else
      {
        temp = this->First(k->data);
        cout << "\tCo first(" << k->data;
      }
      cout << ") = {" << temp << "}" << endl;
      for (Node<string> *t = temp.head; t != NULL; t = t->next)
      {
        if (t == temp.head)
        {
          cout << "\t";
        };
        cout << "M[" << p->data.A << "," << t->data << "] = ";
      }
      Prod prod;
      prod.A = p->data.A;
      prod.alpha.AddTail(k->data);
      cout << prod << endl;
    }
  }
}

void M::PrintTable() const
{
  if (this->list_sigma.Size() > 14)
  {
    cout << "Bang qua dai, in ra xau nen khong in !" << endl;
    return;
  }
  int columnWitdh = 9, halfColumn = columnWitdh / 2, t = halfColumn - 2, f = t + halfColumn;
  printSpam("_", 3); // w = 7 -> 8, w = 9 -> 11
  printSpam("_", halfColumn);
  printHorizontalLine(columnWitdh + 2, this->list_sigma.Size(), "_", "", "_");
  cout << "|  ";
  printSpecial(" ", halfColumn);
  for (Node<string> *p = this->list_sigma.head; p != NULL; p = p->next)
  {
    string temp = p->data;
    printSpecial(temp, f, halfColumn);
  }
  cout << endl;
  cout << "|--";
  printSpam("-", halfColumn);
  printHorizontalLine(columnWitdh + 2, this->list_sigma.Size(), "|", "");
  // In từng hàng và giá trị tương ứng
  for (Node<string> *p = this->list_delta.head; p != NULL; p = p->next)
  {
    string temp1 = p->data;
    cout << "|  ";
    printSpecial(temp1, halfColumn);
    for (Node<string> *t = this->list_sigma.head; t != NULL; t = t->next)
    {
      Prod prod = (*this)(p->data, t->data);
      if (prod.alpha.isEmpty())
      {
        printSpecial(" ", f, halfColumn);
      }
      else
      {
        string x = prod.alpha.getHead();
        printSpecial(x, f, halfColumn);
      }
    }
    cout << endl;
    string wall_left = "|", sSpam = "-";
    if (p->next == NULL)
    {
      wall_left = "¯";
      sSpam = "¯";
    }
    cout << wall_left << sSpam << sSpam;
    printSpam(sSpam, halfColumn);
    printHorizontalLine(columnWitdh + 2, this->list_sigma.Size(), wall_left, "", sSpam);
  }
}

void M::PrintListRCP() const
{
  for (Node<RCP> *p = this->data.head; p != NULL; p = p->next)
  {
    cout << p->data << endl;
  }
}

LinkedList<string> M::First(string x)
{
  LinkedList<string> output;
  this->FirstLoop(x, output);
  return output;
}

LinkedList<string> M::Follow(string A)
{
  LinkedList<string> output, tracer;
  return this->FollowTemp(A, tracer).beContainUniqueItem();
}

LinkedList<Prod> M::getProdContainA(string A)
{
  LinkedList<Prod> output;
  Prod prod;
  for (Node<Prod> *p = this->list_prod.head; p != NULL; p = p->next)
  {
    for (Node<string> *k = p->data.alpha.head; k != NULL; k = k->next)
    {
      if (isSubstring(k->data, A) && (A != p->data.A))
      {
        prod.A = p->data.A;
        prod.alpha.AddTail(k->data);
        output.AddTail(prod);
        prod.alpha.Destroy();
      }
    }
  }
  return output;
}

Prod M::getProd(string A) const
{
  Prod prod;
  for (Node<Prod> *p = this->list_prod.head; p != NULL; p = p->next)
  {
    if (p->data.A == A)
      prod = p->data;
  }
  return prod;
}

Prod M::operator()(const string &A, const string &alpha) const
{
  Pair<string, string> pair(A, alpha);
  Prod prod;
  for (Node<RCP> *p = this->data.head; p != NULL; p = p->next)
  {
    if (p->data.pair == pair)
    {
      return p->data.value;
    }
  }
  return prod;
}

string M::getNextA(string A, const Prod &prod)
{
  string output = "ε";
  LinkedList<string> temp = getToken_Lord(prod.alpha.head->data);
  for (Node<string> *p = temp.head; p != NULL; p = p->next)
  {
    if (A == p->data)
    {
      if (p->next != NULL)
      {
        output = p->next->data;
      }
      break;
    }
  }
  return output;
}

ostream &operator<<(ostream &out, const M &m)
{
  cout << "Bang Tien Đoan M " << endl;
  int columnWidth = 10, numberColumn = m.list_sigma.Size() + 1;
  if (m.list_sigma.Size() > 14)
  {
    cout << "Bang qua dai, in ra xau nen khong in !" << endl;
    return out;
  }
  printHorizontalLine(columnWidth, numberColumn, "_", "_");
  printCenteredString("", columnWidth, "|");
  for (Node<string> *p = m.list_sigma.head; p != NULL; p = p->next)
  {
    printCenteredString(p->data, columnWidth, "|");
  }
  out << endl;
  printHorizontalLine(columnWidth, numberColumn, "|");
  // In từng hàng và giá trị tương ứng
  for (Node<string> *p = m.list_delta.head; p != NULL; p = p->next)
  {
    printCenteredString(p->data, columnWidth, "|");
    for (Node<string> *t = m.list_sigma.head; t != NULL; t = t->next)
    {
      Prod prod = m(p->data, t->data);
      if (prod.alpha.isEmpty())
      {
        printCenteredString("", columnWidth, "|");
      }
      else
      {
        string x = prod.alpha.getHead();
        int i = 0;
        if (x == "ε")
          i = 1;
        printCenteredString(prod.alpha.getHead(), columnWidth + i, "|");
      }
    }
    out << endl;
    string symbol = "|", sSpam = "-";
    if (p->next == NULL)
    {
      symbol = "¯";
      sSpam = "¯";
    }
    printHorizontalLine(columnWidth, numberColumn, symbol, sSpam);
  }
  return out;
}

M::M(const LinkedList<Prod> &list_prod, const LinkedList<string> &delta, const LinkedList<string> &sigma)
{
  this->list_delta = delta;
  this->list_sigma = sigma;
  list_sigma.AddTail("$");
  this->list_prod = list_prod;
  for (Node<Prod> *p = list_prod.head; p != NULL; p = p->next)
  {
    for (Node<string> *k = p->data.alpha.head; k != NULL; k = k->next)
    {
      LinkedList<string> temp;
      if (k->data == "ε")
      {
        temp = this->Follow(p->data.A);
      }
      else
      {
        temp = this->First(k->data);
      }
      for (Node<string> *t = temp.head; t != NULL; t = t->next)
      {
        Prod prod;
        prod.A = p->data.A;
        prod.alpha.AddTail(k->data);
        Pair<string, string> pair(p->data.A, t->data);
        RCP rcp(pair, prod);
        this->data.AddTail(rcp);
      }
    }
  }
}

M::~M()
{
  this->data.Destroy();
  this->list_delta.Destroy();
  this->list_sigma.Destroy();
};

void M::FirstLoop(string x, LinkedList<string> &output)
{
  string A = getToken_Lord(x).getHead(); // Lấy A là ký hiệu đầu tiên trong chuỗi
  if (this->list_sigma.isExist(A) || A == "ε")
  { // Nếu A ∈ Σ, lấy A
    output.AddTail(A);
    return;
  }
  else
  { // Nếu A ∈ Δ, tìm sản xuất của A
    Prod prod = this->getProd(A);
    for (Node<string> *p = prod.alpha.head; p != NULL; p = p->next)
    {                                                 // Tương ứng với mỗi α, xét tương tự
      string temp = getToken_Lord(p->data).getHead(); // Lấy ký hiệu đầu của từng α
      if (this->list_sigma.isExist(temp) || temp == "ε")
      { // Kiểm tra α ∈ Σ thì lấy
        output.AddTail(temp);
      }
      else
      {
        LinkedList<string> tempOutput; // Nếu không, tiếp tục tìm sản xuất và lặp đến khi tìm được A ∈ Σ, rồi lưu vào biến tạm
        this->FirstLoop(temp, tempOutput);
        for (Node<string> *q = tempOutput.head; q != NULL; q = q->next)
        {
          output.AddTail(q->data); // thêm kết quả tìm được vào output
        }
      }
    }
  }
}

LinkedList<string> M::FollowTemp(string A, LinkedList<string> &tracer)
{
  LinkedList<string> output;
  if (tracer.isExist(A))
    return output; // Nếu đã quét qua A rồi thì ngừng quét
  return this->FindFollow(A, tracer);
}

LinkedList<string> M::FindFollow(string A, LinkedList<string> &tracer)
{
  tracer.AddTail(A);
  LinkedList<string> output;
  if (A == this->list_prod.getHead().A)
  { // Nếu A là s, thêm $ vào follow(A)
    output.AddTail("$");
  }
  LinkedList<Prod> list_prod = this->getProdContainA(A); // Lấy ra các sản xuất có chứa A
  for (Node<Prod> *p = list_prod.head; p != NULL; p = p->next)
  { // Duyệt qua các sản xuất đã tìm được
    for (Node<string> *k = p->data.alpha.head; k != NULL; k = k->next)
    { // Duyệt qua các α
      Prod prod;
      prod.A = p->data.A;
      prod.alpha.AddTail(k->data);             // Tạo Prod lẻ với mỗi alpha
      string next_A = this->getNextA(A, prod); // Lấy ký hiệu bên phải A
      if (next_A != "ε")
      { // Trường hợp A ∈ K -> αAẞ
        if (this->list_sigma.isExist(next_A))
        { // Nếu ẞ ∈ Σ, follow(A) += ẞ
          output.AddTail(next_A);
        }
        else
        {
          LinkedList<string> first_temp = this->First(next_A);
          for (Node<string> *t = first_temp.head; t != NULL; t = t->next)
          {
            if (t->data == "ε")
            { // với ε ∈ first(ẞ), follow(A) += follow(K)
              output += this->FollowTemp(prod.A, tracer);
            }
            else
            { // với ε ∉ first(ẞ), follow(A) += first(ẞ)
              output.AddTail(t->data);
            }
          }
        }
      }
      else
      { // Trường hợp A ∈ K -> αA
        output += this->FollowTemp(prod.A, tracer);
      }
    }
  }
  return output.beContainUniqueItem();
}

#endif