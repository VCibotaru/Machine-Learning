build/bin/task2 -d ../data/binary/train_labels.txt -m model.txt --train;
echo "Training done";
build/bin/task2 -d ../data/binary/test_labels.txt -m model.txt -l predictions.txt --predict;
echo "Prediction done";
python compare.py ../data/binary/test_labels.txt predictions.txt