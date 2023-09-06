package com.paulocoutinho.jnibindtest

import android.os.Bundle
import androidx.appcompat.app.AppCompatActivity
import com.paulocoutinho.jnibindtest.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)

        // Example of a call to a native method
        binding.sampleText.text = stringFromJNI()
        binding.sampleText.text = binding.sampleText.text.toString() + "\n\n"
        binding.sampleText.text = binding.sampleText.text.toString() + testJNI("my test")
    }

    /**
     * A native method that is implemented by the 'jnibindtest' native library,
     * which is packaged with this application.
     */
    external fun stringFromJNI(): String
    external fun testJNI(name: String): Boolean
}