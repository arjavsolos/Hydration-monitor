# Non-Invasive Hydration Monitor with Real-Time ML Classification

This project presents a novel, end-to-end system for monitoring human hydration status non-invasively using a Galvanic Skin Response (GSR) sensor. Traditional methods for assessing hydration are often invasive and require clinical settings. This solution provides a cost-effective, real-time alternative by combining a wearable ESP32-based sensor with a cloud-connected machine learning pipeline and an interactive user interface.




Key Features

Non-Invasive Sensing: Uses Galvanic Skin Response (GSR) to measure skin conductance, which correlates with the body's hydration level.



Real-Time Data Logging: An ESP32 microcontroller captures sensor data and logs it to a cloud database every 10 seconds.



Machine Learning Classification: A Random Forest model classifies GSR readings as 'Hydrated' or 'Dehydrated' with high accuracy.




Interactive Dashboard: A Streamlit web application provides a user-friendly interface for live monitoring, classification, and personalized health advice.
