### Font cutting
ほとんどのプロジェクトでは、カスタムフォントを使用します。しかし、いくつかのフォントは、非常に大きなサイズでプロジェクトに適していないことがあります。 また、フォントの特定の文字のみを使用する場合に必要なフォントだけを切り取って使用すると、フォントが占めるシェアを減らして全体的なパフォーマンスの向上にも非常に役立つことができます。

### Font cutting toolの使用
上部メニューの**Toos**で**Font cutting tool**を見つけることができます。

  ![](assets/ide/font_cut_tool_menu.png)

  ![](assets/ide/font_cut_tool.png)

1. まず、「Set the font cutting method"を設定します。ここでいくつかの文字を使用するかを決定します。
   * Regular expression   
      java正規表現をサポートします。例：`\ d`は、すべての数値を意味します。
   * Specify text  
     特定**、**UTF-8でエンコードされた** txtファイル内のコンテンツだけでフォントを再構成します。（推奨する方法で、シンプルで直感的です。）
   
2. Set the font  
   使用するフォントを設定します。
    
3. Set the output path  
   再構成されたフォントが保存されるパスを設定します。もし既存のために作らフォントファイルがある場合は、新しいファイルに置き換えられます。
    
4. すべての設定が終わった後**Cut**をクリックします。

5. もし完了メッセージが表示される場合に成功したものであり、新たなフォントが設定されたout pathに作成されます。

### 例
新しいtxtファイルを作成し、 "Hellow」という単語のみを追加した後** UTF-8**形式で保存してください。その後** Font cutting tool**にパラメータを設定し、** Cut**ボタンを押すと、10KB以下のttfファイルが作成されたことを確認することができます。[Online Font Editor](http://fontstore.baidu.com/static/editor/index.html)などでこのフォントは、唯一のtxtファイルの中の文字だけを含んでいることを確認することができます。

![](assets/ide/font_cut_tool_test.png)


