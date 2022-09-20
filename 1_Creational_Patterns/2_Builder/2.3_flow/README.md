# 2.3 흐름식 빌더

```c++
HtmlBuilder& add_child(std::string child_name, std::string child_text)
{
    HtmlElement e{child_name, child_text};
    root.elements.emplace_back(e);

    return *this;
}
```
```c++
HtmlBuilder builder{"ul"};    
builder.add_child("li", "hello").add_child("li", "world");
```
 위처럼 멤버 메서드가 자기 자신을 참조로 반환함으로서 메서드들이 꼬리에 꼬리를 무는 호출이 가능해진다.
 이러한 형태로 호출 하는 것을 흐름식 인터페이스(fluent interface)라한다.