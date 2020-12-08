# <span id="new_flythings_project">新しいFlywizOSプロジェクトを作成する</span>
 新しいFlywizOSプロジェクトを作成することは非常に簡単です。具体的な手順は次のとおりです :
1. IDEの上部のメニューバーから**File->New->FlywziOS Application Project**を選択します。

   ![](assets/ide/new_flythings_project.gif)  

2. 先の選択が完了したら、** FlywizOS New Wizard**がポップアップされます。     
   ![](assets/ide/wizard_new_project_page1.png)  
   新しいプロジェクトを作るのに必要なパラメータを入力します。

   * **Project name**  
    プロジェクトの名前です。数字と文字の組み合わせで作成することができます。
   * **Location**  
    プロジェクトが保存されるパスです。
   * **Platform**  
    所有しているボードに合ったプラットフォームを選択してください。
     - **F9311**  
     - **F9306**  
   
   上記のパラメータを満たした後、すぐに**Finish**をクリックすると、プロジェクトが作成されます。しかし、今では、より多くの設定のために**Next**を選択します。   
3. Nextをクリックした後、以下のようなパラメータを見ることができます。     
   ![](assets/ide/wizard_new_project_page2.png)      
   
   ## プロジェクトの各属性の意味と機能
   * **Screen saver timeout**  
   
    FlywizOSシステムはスクリーンセーバー機能を提供します。もし、特定の時間内にタッチ操作がないか、コードを介してスクリーンセーバーの時間をリセットしない場合、システムは自動的にスクリーンセーバーに入ります。
    時間が **-1**場合スクリーンセーバー機能を使用しないということを意味します。
   
   * **Serial port**  
    通信シリアルポートであり、一般的に変更する必要がありません。
   
   * **Baud rate**   
    通信用シリアルポートのBaud rateです。
   
   * **Resolution**  
    スクリーンのwidthとheightです。単位はピクセルです。

   * **Screen rotation**  
    画面の表示方向を設定することができます。
   
   * **Font**  
    FlywizOSはcustom fontをサポートします。もし基本的なフォントが満足していない場合は、**Default**を解除して使用するフォントを選択することができます。
   
   * **Input method**  
    もし中国語入力が必要な場合選択してください。そして **[Edit Text](edittext.md)**コントロールの中国語入力を解決します。

   Don't worry about satisfying this, as the above attributes can be changed again later. ([How to change project properties](set_project_properties.md)) 
   入力されたすべてのプロパティを確認し、**Finish**をクリックすると、プロジェクトの作成が終了します。作成プロセスには、いくつかの時間がかかりますので、しばらくお待ちください。  

4. プロジェクトが作成されると、まず、[FlywizOSプロジェクトコード構造](project_structure＃project_structure.md)を理解する必要があります。

