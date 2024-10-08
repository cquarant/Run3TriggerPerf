today=`date "+%Y%m%d"`


sed -i -e "s/isData = False/isData = True/" config_generic_opt_skimmed.py
sed -i -e "s/config\[\"ISBKG\"\] = True/config\[\"ISBKG\"\] = False/" config_generic_opt_skimmed.py

#for year in 2016
for year in 2018
do
    echo $year
#    postfix="den_data_${year}"
#    postfix="Legacy_q3_${year}_${today}"
    postfix="JpsiK_purity_${year}_${today}"

    python submit_all.py -d crab/Crab_${today}_${postfix} -c config_generic_opt_skimmed.py -f samples/EphemeralZeroBias.txt -s "_v1" --string "${postfix}"  --luminosity --isData
done


