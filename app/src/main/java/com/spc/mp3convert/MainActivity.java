package com.spc.mp3convert;

        import android.os.Bundle;
        import android.os.Environment;
        import android.support.v7.app.AppCompatActivity;
        import android.view.View;
        import android.widget.Toast;

        import java.io.File;

        public class MainActivity extends AppCompatActivity {

            @Override
            protected void onCreate(Bundle savedInstanceState) {
                super.onCreate(savedInstanceState);
                setContentView(R.layout.activity_main);
    }

    public void onclick1(View view) {
        Toast.makeText(MainActivity.this, NativesMethods.getLameVersion(), Toast.LENGTH_SHORT).show();

    }

    public void onclick2(View view) {
        final File path = Environment.getExternalStorageDirectory();
        File file = new File(path.getAbsolutePath() + "/test.wav");
        new Thread() {
            @Override
            public void run() {
                NativesMethods.read(path.getAbsolutePath() + "/test.wav", path.getAbsolutePath() + "/out.mp3");
            }
        }.start();


    }

}

