package com.example.myapplication

import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.util.Log
import android.view.View
import android.widget.AdapterView
import android.widget.ArrayAdapter
import android.widget.Toast
import com.example.myapplication.databinding.ActivityMainBinding
import com.google.firebase.database.*
import com.google.firebase.database.FirebaseDatabase.*

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding
    private lateinit var database: DatabaseReference
    private var TAG = "MainActivity"
    private var itemGlobal: String = "01"

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        setBedNo()
        getValue("01")
        buttonClick()
        database = getInstance().getReference("BedNo")
        database.child(itemGlobal).addValueEventListener(object: ValueEventListener {

            override fun onDataChange(snapshot: DataSnapshot) {
                binding.textMsg.text = snapshot.child("Message").value.toString()
            }

            override fun onCancelled(error: DatabaseError) {
                Log.i(TAG, "Error receiving updates")
            }
        })
    }

    private fun buttonClick() {
        binding.b10min.setOnClickListener{addTime("10min")}

        binding.b20min.setOnClickListener{addTime("20min")}

        binding.bLater.setOnClickListener{addTime("Later")}

        binding.bNurse.setOnClickListener{addTime("Nurse")}
    }

    private fun setBedNo() {
        val items = arrayOf("01","02","03","04")
        val adapter = ArrayAdapter(applicationContext,android.R.layout.simple_spinner_dropdown_item,items)
        binding.spinnerBedno.adapter = adapter
        binding.spinnerBedno.onItemSelectedListener = object : AdapterView.OnItemSelectedListener {
            override fun onNothingSelected(parent: AdapterView<*>?) {
                Log.i(TAG, "Nothing Selected")
            }
            override fun onItemSelected(parent: AdapterView<*>?, view: View?, position: Int, id: Long) {
                Log.i(TAG, "Selected: ${items[position]}")
                if(items[position] == "Select BedNo") {
                    Toast.makeText(applicationContext, "Please select a BedNo", Toast.LENGTH_SHORT).show()
                } else {
                    val myItem = items[position]
                    itemGlobal = myItem
                    getValue(myItem)
                }
            }
        }
    }

    private fun addTime(time:String) {
        val waitTime = mapOf<String, String>(
            "Wait Time" to time
        )
        database = getInstance().getReference("BedNo")
        database.child(itemGlobal).updateChildren(waitTime).addOnSuccessListener {
            Log.i(TAG, "Database Updated")
        }.addOnCanceledListener {
            Log.i(TAG, "Database Update Failed")
        }
    }

    private fun getValue(myItem:String) {
        database = getInstance().getReference("BedNo")
        database.child(myItem).get().addOnSuccessListener {

            if(it.exists()) {

                binding.textMsg.text = it.child("Message").value.toString()
                binding.textName.text = it.child("Name").value.toString()
                binding.textGender.text = it.child("Gender").value.toString()
                binding.textAge.text = it.child("Age").value.toString()
                binding.textCond.text = it.child("Condition").value.toString()
                binding.bLater.isEnabled = true
                binding.b10min.isEnabled = true
                binding.bNurse.isEnabled = true
                binding.b20min.isEnabled = true

            } else {
                Toast.makeText(applicationContext, "No such BedNo", Toast.LENGTH_SHORT).show()
                binding.textMsg.text = ""
                binding.textName.text = ""
                binding.textGender.text = ""
                binding.textAge.text = ""
                binding.textCond.text = ""
                binding.bLater.isEnabled = false
                binding.b10min.isEnabled = false
                binding.bNurse.isEnabled = false
                binding.b20min.isEnabled = false
            }

        }.addOnFailureListener{
            Log.i(TAG, "Failed to retrieve data")
        }
    }

}