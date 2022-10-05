package com.kiseong.closet;

import androidx.annotation.NonNull;
import androidx.appcompat.app.AppCompatActivity;

import android.os.Bundle;
import android.view.Gravity;
import android.view.View;
import android.webkit.WebSettings;
import android.webkit.WebView;
import android.webkit.WebViewClient;
import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;
import android.widget.Toast;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.Query;
import com.google.firebase.database.ValueEventListener;

public class MainActivity extends AppCompatActivity {

    private TextView txtTemp;
    private EditText editText;
    private Button button1;
    private Button button2;

    private FirebaseDatabase database;
    private DatabaseReference databaseReference;

   DatabaseReference motherRootRef = FirebaseDatabase.getInstance().getReference();
   DatabaseReference modeRef=motherRootRef.child("mode");
    DatabaseReference temperatureRef=motherRootRef.child("mode");



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        database = FirebaseDatabase.getInstance();
        databaseReference = database.getReference("user");
        //database
        modeRef.setValue(0);

    }


    @Override
        protected void onStart(){
        super.onStart();



        findViewById(R.id.btnLockOpen).setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                modeRef.setValue(2); // 데이터 베이스에 출력 코드
                Toast toast = Toast.makeText(getApplicationContext(),"LED를 끕니다.",Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.CENTER | Gravity.BOTTOM,0,20);
                toast.show();
            }


        });

        findViewById(R.id.btnLock).setOnClickListener(new View.OnClickListener() {
            @Override
            public void onClick(View view) {
                modeRef.setValue(1);
                Toast toast = Toast.makeText(getApplicationContext(),"LED를 킵니다.",Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.CENTER | Gravity.BOTTOM,0,20);
               toast.show();
            }
        });
        findViewById(R.id.btncooler).setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                modeRef.setValue(5); // 데이터 베이스에 출력 코드
                Toast toast = Toast.makeText(getApplicationContext(),"Fan을 회전시킵니다.",Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.CENTER | Gravity.BOTTOM,0,20);
                toast.show();
            }
        });
        findViewById(R.id.btncoolstop).setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                modeRef.setValue(6); // 데이터 베이스에 출력 코드
                Toast toast = Toast.makeText(getApplicationContext(),"Fan을 정지합니다.",Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.CENTER | Gravity.BOTTOM,0,20);
                toast.show();
        }});

        findViewById(R.id.btnOpen).setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                modeRef.setValue(3); // 데이터 베이스에 출력 코드
                Toast toast = Toast.makeText(getApplicationContext(),"문을 개방합니다.",Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.CENTER | Gravity.BOTTOM,0,20);
                toast.show();
            }
        });

        findViewById(R.id.btnClose).setOnClickListener(new View.OnClickListener(){
            @Override
            public void onClick(View view){
                modeRef.setValue(4); // 데이터 베이스에 출력 코드
                Toast toast = Toast.makeText(getApplicationContext(),"문을 닫습니다..",Toast.LENGTH_SHORT);
                toast.setGravity(Gravity.CENTER | Gravity.BOTTOM,0,20);
                toast.show();
            }

        });




        WebView webView = (WebView)findViewById(R.id.webView);
        webView.setWebViewClient(new WebViewClient());
        webView.setBackgroundColor(125);


        WebSettings webSettings = webView.getSettings();
        webSettings.setJavaScriptEnabled(true);

     

        webView.loadDataWithBaseURL("http://192.168.143.1:8080/stream","<html><head></head><body>"+
                        "<img src='/stream/video.mjpeg' alt='image'></body></html>",
                "text/html", "UTF-8","");

    }
//화면 크기 406 400


}
