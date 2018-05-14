<?php

if(!isset($_POST['submit']))
{
	//This page should not be accessed directly. Need to submit the form.
	echo "error; you need to submit the form!";
}

$name = $_POST['name'];
$pass = $_POST['pass'];
$Qsensor = $_POST['Qsensor'];
$Qactuator = $_POST['Qactuator'];
$Qconfig = $_POST['Qconfig'];
$Qrule = $_POST['Qrule'];
$Qother = $_POST['Qother'];
$link = $print_connect  = "";
$print_tableA = $print_tableR = $print_tableC = $print_tableO = $print_tableS = "<br>";
$print_queryA = $print_queryR = $print_queryC = $print_queryS = $print_queryO = "";
$numrowsA = $numrowsR = $numrowsC = $numrowsS = $numrowsO = "";
$numfieldsA = $numfieldsR = $numfieldsC = $numfieldsS = $numfieldsO = "";
$SdataPoints = array();
$AdataPoints = array();
$C1dataPoints = array();
$C2dataPoints = array();
$RdataPoints = array();
$R1dataPoints = array();
$R2dataPoints = array();
$QComplexity = $_POST['Complexity'];
$Debug = $_POST['Debug'];

//grafical variables Config
$CfieldDivision = "room";
$CfieldQuantS = "sensor";
$CfieldQuantA = "actuator";

//grafical variables Sensor
$SfieldTime = "timestamp";
$SfieldReading = "measurement";

$SfieldDivision = "room";
$SfieldAverage = "average";

//grafical variables Actuator
$AfieldDivision = "room";
$AfieldChange = "change";

//grafical variables Rules
$RfieldQuant = "rules";
$RfieldDivision = "room";

$RfieldRead = "measurement";
$RfieldRef = "reference";
$RfieldTime = "timestamp";

//db connection
if(empty($name)||empty($pass)) {
     $print_connect = "User and Password are mandatory!";
    exit;
} else{
   $connect_sting = "host=db.fe.up.pt dbname=" . $name . " user=" . $name . " password=" . $pass;

   $link = pg_Connect($connect_sting);
   if(!$link) {
         $print_connect = "Error : Unable to open database";
      } else {
         $print_connect = "Opened database successfully";

		}
	}

//Query for sensor
if(!empty($Qsensor)){

	$resultS = pg_exec($link, $Qsensor);
	if(!$resultS) {

	$print_queryS = "Query «" . $Qsensor . "» error: " . pg_last_error($link);
		} else {
			$print_queryS = "Query «" . $Qsensor . "» executed successfully";

			$numrowsS = pg_numrows($resultS);
			$numfieldsS = pg_num_fields($resultS);

			if($QComplexity == "Easy"){

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsS; $ri++) {
				 $rowS = pg_fetch_array($resultS, $ri);
				 $time = (string)$rowS[$SfieldTime];
				 $print_tableS .= $SfieldTime . "= " . $rowS[$SfieldTime] . " " . $SfieldReading . "= " . $rowS[$SfieldReading];
				 array_push($SdataPoints, array("label" => $time, "y" => $rowS[$SfieldReading]));
				}

			}elseif ($QComplexity == "Medium") {

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsS; $ri++) {
				 $rowS = pg_fetch_array($resultS, $ri);
				 $division = (string)$rowS[$SfieldDivision];
				 $print_tableS .= $SfieldDivision . "= " . $rowS[$SfieldDivision] . " " . $SfieldAverage . "= " . $rowS[$SfieldAverage];
				 array_push($SdataPoints, array("label" => $division, "y" => $rowS[$SfieldAverage]));

				}

			}elseif ($QComplexity == "Hard") {
				$print_tableS = "<tr>";
			 // Loop on fields in the result set.
			 for ($j = 0; $j < $numfieldsS; $j++) {
						$fieldnameS = pg_field_name($resultS, $j);
						$print_tableS .= "<th> $fieldnameS </th>";
				}
				$print_tableS .= "</tr>";

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsS; $ri++) {
				 $print_tableS .= "<tr>";
				 $rowS = pg_fetch_array($resultS, $ri);

				 for ($j = 0; $j < $numfieldsS; $j++) {
							$fieldnameS = pg_field_name($resultS, $j);
							$print_tableS .= "<td>" . $rowS[$fieldnameS] . "</td>";
					}
					$print_tableS .=  "</tr>";
				}
			}else {
				// code...
			}

		}
}

//Query for actuator
if(!empty($Qactuator)){

	$resultA = pg_exec($link, $Qactuator);
	if(!$resultA) {

	$print_queryA = "Query «" . $Qactuator . "» error: " . pg_last_error($link);
		} else {
			$print_queryA = "Query «" . $Qactuator . "» executed successfully";

			$numrowsA = pg_numrows($resultA);
			$numfieldsA = pg_num_fields($resultA);


			if($QComplexity == "Easy"){
				$print_tableA = "<tr>";
			 // Loop on fields in the result set.
			 for ($j = 0; $j < $numfieldsA; $j++) {
						$fieldnameA = pg_field_name($resultA, $j);
						$print_tableA .= "<th> $fieldnameA </th>";
				}
				$print_tableA .= "</tr>";

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsA; $ri++) {
				 $print_tableA .= "<tr>";
				 $rowA = pg_fetch_array($resultA, $ri);

				 for ($j = 0; $j < $numfieldsA; $j++) {
							$fieldnameA = pg_field_name($resultA, $j);
							$print_tableA .= "<td>" . $rowA[$fieldnameA] . "</td>";
					}
					$print_tableA .=  "</tr>";
				}

			}elseif ($QComplexity == "Medium") {

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsA; $ri++) {
				 $rowA = pg_fetch_array($resultA, $ri);
				 $division = (string)$rowA[$AfieldDivision];
				 $print_tableA .= $AfieldDivision . "= " . $rowA[$AfieldDivision] . " " . $AfieldChange . "= " . $rowA[$AfieldChange];
				 array_push($AdataPoints, array("label" => $division, "y" => $rowA[$AfieldChange]));

				}

			}elseif ($QComplexity == "Hard") {
				$print_tableA = "<tr>";
			 // Loop on fields in the result set.
			 for ($j = 0; $j < $numfieldsA; $j++) {
						$fieldnameA = pg_field_name($resultA, $j);
						$print_tableA .= "<th> $fieldnameA </th>";
				}
				$print_tableA .= "</tr>";

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsA; $ri++) {
				 $print_tableA .= "<tr>";
				 $rowA = pg_fetch_array($resultA, $ri);

				 for ($j = 0; $j < $numfieldsA; $j++) {
							$fieldnameA = pg_field_name($resultA, $j);
							$print_tableA .= "<td>" . $rowA[$fieldnameA] . "</td>";
					}
					$print_tableA .=  "</tr>";
				}
			}else {
				// code...
			}
}

}

//Query for Configuration
if(!empty($Qconfig)){

	$resultC = pg_exec($link, $Qconfig);
	if(!$resultC) {

	$print_queryC = "Query «" . $Qconfig . "» error: " . pg_last_error($link);
		} else {
			$print_queryC = "Query «" . $Qconfig . "» executed successfully";

			$numrowsC = pg_numrows($resultC);
			$numfieldsC = pg_num_fields($resultC);


			if($QComplexity == "Easy"){
				$print_tableC = "<tr>";
			 // Loop on fields in the result set.
			 for ($j = 0; $j < $numfieldsC; $j++) {
						$fieldnameC = pg_field_name($resultC, $j);
						$print_tableC .= "<th> $fieldnameC </th>";
				}
				$print_tableC .= "</tr>";

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsC; $ri++) {
				 $print_tableC .= "<tr>";
				 $rowC = pg_fetch_array($resultC, $ri);

				 for ($j = 0; $j < $numfieldsC; $j++) {
							$fieldnameC = pg_field_name($resultC, $j);
							$print_tableC .= "<td>" . $rowC[$fieldnameC] . "</td>";
					}
					$print_tableC .=  "</tr>";
				}

			}elseif ($QComplexity == "Medium") {

				$print_tableC = "<tr>";
			 // Loop on fields in the result set.
			 for ($j = 0; $j < $numfieldsC; $j++) {
						$fieldnameC = pg_field_name($resultC, $j);
						$print_tableC .= "<th> $fieldnameC </th>";
				}
				$print_tableC .= "</tr>";

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsC; $ri++) {
				 $print_tableC .= "<tr>";
				 $rowC = pg_fetch_array($resultC, $ri);

				 for ($j = 0; $j < $numfieldsC; $j++) {
							$fieldnameC = pg_field_name($resultC, $j);
							$print_tableC .= "<td>" . $rowC[$fieldnameC] . "</td>";
					}
					$print_tableC .=  "</tr>";
				}

			}elseif ($QComplexity == "Hard") {

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsC; $ri++) {
				 $rowC = pg_fetch_array($resultC, $ri);
				 $division = (string)$rowC[$CfieldDivision];
				 $print_tableC .= $CfieldDivision . "= " . $rowC[$CfieldDivision] . " " . $CfieldQuantS . "= " . $rowC[$CfieldQuantS] . " " . $CfieldQuantA . "= " . $rowC[$CfieldQuantA];
				 array_push($C1dataPoints, array("label" => $division, "y" => $rowC[$CfieldQuantS]));
				 array_push($C2dataPoints, array("label" => $division, "y" => $rowC[$CfieldQuantA]));

				}
			}else {
				// code...
			}
}

}

//Query for Rules
if(!empty($Qrule)){

	$resultR = pg_exec($link, $Qrule);
	if(!$resultR) {

	$print_queryR = "Query «" . $Qrule . "» error: " . pg_last_error($link);
		} else {
			$print_queryR = "Query «" . $Qrule . "» executed successfully";

			$numrowsR = pg_numrows($resultR);
			$numfieldsR = pg_num_fields($resultR);

			if($QComplexity == "Easy"){
				$print_tableR = "<tr>";
			 // Loop on fields in the result set.
			 for ($j = 0; $j < $numfieldsR; $j++) {
						$fieldnameR = pg_field_name($resultR, $j);
						$print_tableR .= "<th> $fieldnameR </th>";
				}
				$print_tableR .= "</tr>";

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsR; $ri++) {
				 $print_tableR .= "<tr>";
				 $rowR = pg_fetch_array($resultR, $ri);

				 for ($j = 0; $j < $numfieldsR; $j++) {
							$fieldnameR = pg_field_name($resultR, $j);
							$print_tableR .= "<td>" . $rowR[$fieldnameR] . "</td>";
					}
					$print_tableR .=  "</tr>";
				}

			}elseif ($QComplexity == "Medium") {

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsR; $ri++) {
				 $rowR = pg_fetch_array($resultR, $ri);
				 $division = (string)$rowR[$RfieldDivision];
				 $print_tableR .= $RfieldDivision . "= " . $rowR[$RfieldDivision] . " " . $RfieldQuant . "= " . $rowR[$RfieldQuant];
				 array_push($RdataPoints, array("label" => $division, "y" => $rowR[$RfieldQuant]));
			 }

			}elseif ($QComplexity == "Hard") {

				// Loop on rows in the result set.
				for($ri = 0; $ri < $numrowsR; $ri++) {
				 $rowR = pg_fetch_array($resultR, $ri);
				 $time = (string)$rowR[$RfieldTime];
				 $print_tableR .= $RfieldTime . "= " . $rowR[$RfieldTime] . " " . $RfieldRef . "= " . $rowR[$RfieldRef] . " " . $RfieldRead . "= " . $rowR[$RfieldRead];
				 array_push($R1dataPoints, array("label" => $time, "y" => $rowR[$RfieldRef]));
				 array_push($R2dataPoints, array("label" => $time, "y" => $rowR[$RfieldRead]));

				}
			}else {
				// code...
			}
}

}

//Other Queries
if(!empty($Qother)){
	$resultO = pg_exec($link, $Qother);
	if(!$resultO) {

	$print_queryO = "Query «" . $Qother . "» error: " . pg_last_error($link);
		} else {
			$print_queryO = "Query «" . $Qother . "» executed successfully";

			$numrowsO = pg_numrows($resultO);
			$numfieldsO = pg_num_fields($resultO);

			$print_tableO = "<tr>";
		 // Loop on fields in the result set.
		 for ($j = 0; $j < $numfieldsO; $j++) {
					$fieldnameO = pg_field_name($resultO, $j);
					$print_tableO .= "<th> $fieldnameO </th>";
			}
			$print_tableO .= "</tr>";

			// Loop on rows in the result set.
			for($ri = 0; $ri < $numrowsO; $ri++) {
			 $print_tableO .= "<tr>";
			 $rowO = pg_fetch_array($resultO, $ri);

			 for ($j = 0; $j < $numfieldsO; $j++) {
						$fieldnameO = pg_field_name($resultO, $j);
						$print_tableO .= "<td>" . $rowO[$fieldnameO] . "</td>";
				}
				$print_tableO .=  "</tr>";
			}
}

}

?>

<!DOCTYPE html>

    <html class="no-js">
    <head>
        <meta charset="utf-8">
        <title>SINF 2017/18</title>
    	  <meta name="description" content="">
		    <meta name="keywords" content="">
        <meta name="viewport" content="width=device-width, initial-scale=1">

        <link href='http://fonts.googleapis.com/css?family=Open+Sans:400,300,600,700,800' rel='stylesheet' type='text/css'>
        <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">
        <link rel="stylesheet" href="css/bootstrap.min.css">
        <link rel="stylesheet" href="css/font-awesome.css">
        <link rel="stylesheet" href="css/animate.css">
        <link rel="stylesheet" href="css/templatemo_misc.css">
        <link rel="stylesheet" href="css/templatemo_style.css">

        <script src="js/vendor/modernizr-2.6.1-respond-1.1.0.min.js"></script>
		    <script language="JavaScript" src="js/gen_validatorv31.js" type="text/javascript"></script>
				<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.12.4/jquery.min.js"></script>

    </head>
    <body>

        <div class="site-main" id="sTop">
            <div class="site-header">
                <div class="container">
                    <div class="row">
                        <div class="col-md-12 text-center">
                        </div> <!-- /.col-md-12 -->
                    </div> <!-- /.row -->
                </div> <!-- /.container -->
                <div class="main-header">
                    <div class="container">
                        <div id="menu-wrapper">
                            <div class="row">
                                <div class="logo-wrapper col-md-4 col-sm-2 col-xs-8">
                                    <h1>
                                        <a href="index.html">Home Automation System</a>
                                    </h1>
                                </div> <!-- /.logo-wrapper -->
                                <div class="col-md-8 col-sm-10 col-xs-4 main-menu text-right">
                                    <ul class="menu-first hidden-sm hidden-xs">
                                        <li><a href="#sensor">Mote</a></li>
                                        <li><a href="#actuators">Actuators</a></li>
                                        <li><a href="#config">Configurations</a></li>
                                        <li><a href="#rules">Control Rules</a></li>
																				<li><a href="#other">Random Query</a></li>
                                    </ul>
                                    <a href="#" class="toggle-menu visible-sm visible-xs"><i class="fa fa-bars"></i></a>
                                </div> <!-- /.main-menu -->
                            </div> <!-- /.row -->
                        </div> <!-- /#menu-wrapper -->
                        <div class="menu-responsive hidden-md hidden-lg">
                            <ul>
                              <li><a href="#sensor">Mote</a></li>
                              <li><a href="#actuators">Actuators</a></li>
                              <li><a href="#config">Configurations</a></li>
                              <li><a href="#rules">Control Rules</a></li>
															<li><a href="#other">Random Query</a></li>
                            </ul>
                        </div> <!-- /.menu-responsive -->
                    </div> <!-- /.container -->
                </div> <!-- /.main-header -->
            </div> <!-- /.site-header -->
            <div class="site-slider">
                <div class="slider">
                    <div class="flexslider">
                        <ul class="slides">
                            <li>
                                <div class="overlay"></div>
                                <img src="images/6c459023a7d25955c32159f7e839d38e.jpg" alt="">
                                <div class="slider-caption visible-md visible-lg">


                                </div>
                            </li>

                        </ul>
                    </div> <!-- /.flexslider -->
                </div> <!-- /.slider -->
            </div> <!-- /.site-slider -->
        </div> <!-- /.site-main -->

        <div class="content-section" id="sensor">
            <div class="container">
                <div class="row">
                    <div class="heading-section col-md-12 text-center">
                        <h2>Mote</h2>
                        <p>View Sensor Readings History</p>
                    </div> <!-- /.heading-section -->
                </div> <!-- /.row -->
								<div class="row" id="Sde_bug">
                  <p>Connection to DB: <?php echo $print_connect; ?></p>
                  <p>Query Execution: <?php echo $print_queryS; ?></p>
                  <p>Number of Rows: <?php echo $numrowsS; ?></p>
                  <p>Numbers of Fields: <?php echo $numfieldsS; ?></p>
									<p>Complexity: <?php echo $QComplexity; ?></p>
									<p>Results: <?php echo $print_tableS; ?></p>
                </div>
								<div class="row">
								<div id="Seasy">
									<div id="chartContainerSeasy" style="height: 370px; width: 100%;"></div>
								</div>
								<div id="Smedium">
									<div id="chartContainerSmedium" style="height: 370px; width: 100%;"></div>
								</div>
								<div id="Shard">
									<div class="w3-container">
                            <table class="w3-table-all w3-centered">
                                  <?php echo $print_tableS; ?>
                            </table>
                  </div>
								</div>
								</div>
            </div> <!-- /.container -->
        </div> <!-- /#sensor -->

        <div class="content-section" id="actuators">
            <div class="container">
                <div class="row">
                    <div class="heading-section col-md-12 text-center">
						            <h2>Actuators</h2>
                        <p>Monitor State of Actuators</p>
                    </div> <!-- /.heading-section -->
                </div> <!-- /.row -->
               <div class="row" id="Ade_bug">
                 <p>Connection to DB: <?php echo $print_connect; ?></p>
                 <p>Query Execution: <?php echo $print_queryA; ?></p>
                 <p>Number of Rows: <?php echo $numrowsA; ?></p>
                 <p>Number of Fields: <?php echo $numfieldsA; ?></p>
								 <p>Complexity: <?php echo $QComplexity; ?></p>
								 <p>Results: <?php echo $print_tableA; ?></p>
               </div>

							<div class="row">
							<div id="Aeasy">
								<div class="w3-container">
													<table class="w3-table-all w3-centered">
																<?php echo $print_tableA; ?>
													</table>
								</div>
							</div>
							<div id="Amedium">
								<div id="chartContainerAmedium" style="height: 370px; width: 100%;"></div>
							</div>
							<div id="Ahard">
								<div class="w3-container">
													<table class="w3-table-all w3-centered">
																<?php echo $print_tableA; ?>
													</table>
								</div>
							</div>
							</div>

            </div> <!-- /.container -->
        </div> <!-- /#actuator-->

        <div class="content-section" id="config">
            <div class="container">
                <div class="row">
                    <div class="heading-section col-md-12 text-center">
                        <h2>Configuration</h2>
                        <p>View and Edit <b><i>HAS</i></b> Configurations</p>
                    </div> <!-- /.heading-section -->
                </div> <!-- /.row -->
								<div class="row" id="Cde_bug">
                  <p>Connection to DB: <?php echo $print_connect; ?></p>
                  <p>Query Execution: <?php echo $print_queryC; ?></p>
                  <p>Number of Rows: <?php echo $numrowsC; ?></p>
                  <p>Number of Fields: <?php echo $numfieldsC; ?></p>
 								 <p>Complexity: <?php echo $QComplexity; ?></p>
 								 <p>Results: <?php echo $print_tableC; ?></p>
                </div>


								<div class="row">
								<div id="Ceasy">
									<div class="w3-container">
														<table class="w3-table-all w3-centered">
																	<?php echo $print_tableC; ?>
														</table>
									</div>
								</div>
								<div id="Cmedium">
									<div class="w3-container">
														<table class="w3-table-all w3-centered">
																	<?php echo $print_tableC; ?>
														</table>
									</div>
								</div>
								<div id="Chard">
									<div id="chartContainerChard" style="height: 370px; width: 100%;"></div>
								</div>
							</div>
            </div> <!-- /.container -->
        </div> <!-- /#config -->

        <div class="content-section" id="rules">
            <div class="container">
                <div class="row">
                    <div class="heading-section col-md-12 text-center">
                        <h2>Control Rules</h2>
                        <p>View and Edit <b><i>HAS</i></b> Control Rules</p>
                    </div> <!-- /.heading-section -->
                </div> <!-- /.row -->
								<div class="row" id="Rde_bug">
                  <p>Connection to DB: <?php echo $print_connect; ?></p>
                  <p>Query Execution: <?php echo $print_queryR; ?></p>
                  <p>Number of Rows: <?php echo $numrowsR; ?></p>
                  <p>Number of Fields: <?php echo $numfieldsR; ?></p>
 								 <p>Complexity: <?php echo $QComplexity; ?></p>
 								 <p>Results: <?php echo $print_tableR; ?></p>
                </div>

								<div class="row">
								<div id="Reasy">
									<div class="w3-container">
														<table class="w3-table-all w3-centered">
																	<?php echo $print_tableR; ?>
														</table>
									</div>
								</div>
								<div id="Rmedium">
									<div id="chartContainerRmedium" style="height: 370px; width: 100%;"></div>
								</div>
								<div id="Rhard">
									<div id="chartContainerRhard" style="height: 370px; width: 100%;"></div>
								</div>
								</div>

            </div> <!-- /.container -->
        </div> <!-- /#rules -->

				<div class="content-section" id="other">
						<div class="container">
								<div class="row">
										<div class="heading-section col-md-12 text-center">
												<h2>Random Query</h2>
										</div> <!-- /.heading-section -->
								</div> <!-- /.row -->
								<div class="row" id="Ode_bug">
                  <p>Connection to DB: <?php echo $print_connect; ?></p>
                  <p>Query Execution: <?php echo $print_queryO; ?></p>
                  <p>Number of Rows: <?php echo $numrowsO; ?></p>
                  <p>Number of Fields: <?php echo $numfieldsO; ?></p>
 								 <p>Complexity: <?php echo $QComplexity; ?></p>
 								 <p>Results: <?php echo $print_tableO; ?></p>
                </div>
                <div class="row">
                  <div class="w3-container">
                            <table class="w3-table-all w3-centered">
                                  <?php echo $print_tableO; ?>
                            </table>
                       </div>
               </div>
						</div> <!-- /.container -->
				</div> <!-- /#rules -->

        <div class="footer">
            <div class="container">
                <div class="row">
                    <div class="col-md-8 col-xs-12 text-left">
                        Copyright © 2017/18 SINF - FEUP
                        </div>

                    <div class="col-md-4 hidden-xs text-right">
                        <a href="#top" id="go-top">Back to top</a>
                    </div> <!-- /.text-center -->
                </div> <!-- /.row -->
            </div> <!-- /.container -->
        </div> <!-- /#footer -->


				<script>

				function myPluginLoadEvent(func) {
    // assign any pre-defined functions on 'window.onload' to a variable
    var oldOnLoad = window.onload;
    // if there is not any function hooked to it
    if (typeof window.onload != 'function') {
        // you can hook your function with it
        window.onload = func
    } else { // someone already hooked a function
        window.onload = function () {
            // call the function hooked already
            oldOnLoad();
            // call your awesome function
            func();
        }
    }
}

// pass the function you want to call at 'window.onload', in the function defined above
myPluginLoadEvent(function(){
    // your awesome code to run on window.onload
		//alert('window loaded');

	var debug = <?php echo json_encode($Debug); ?>;
	var radio = <?php echo json_encode($QComplexity); ?>;
	var Qsensor = <?php echo json_encode($Qsensor); ?>;
	var Qactuator = <?php echo json_encode($Qactuator); ?>;
	var AfieldChange = <?php echo json_encode($AfieldChange); ?>;
	var Qconfig = <?php echo json_encode($Qconfig); ?>;
	var CfieldQuantS = <?php echo json_encode($CfieldQuantS); ?>;
	var CfieldQuantA = <?php echo json_encode($CfieldQuantA); ?>;
	var Qrule = <?php echo json_encode($Qrule); ?>;
	var RfieldRead = <?php echo json_encode($RfieldRead); ?>;
	var RfieldRef = <?php echo json_encode($RfieldRef); ?>;
	var RfieldQuant = <?php echo json_encode($RfieldQuant); ?>;

//	var Qother = <?php echo json_encode($Qother); ?>;

//alert('window loaded' + Qconfig);
//	alert("radio =" + radio + " config = " + Qconfig);

		//Show and Hide Debug printing messages
		if(debug == "ON"){
			document.getElementById('Sde_bug').style.display = 'inline';
			document.getElementById('Ade_bug').style.display = 'inline';
			document.getElementById('Cde_bug').style.display = 'inline';
			document.getElementById('Rde_bug').style.display = 'inline';
			document.getElementById('Ode_bug').style.display = 'inline';

		}else {
			document.getElementById('Sde_bug').style.display = 'none';
			document.getElementById('Ade_bug').style.display = 'none';
			document.getElementById('Cde_bug').style.display = 'none';
			document.getElementById('Rde_bug').style.display = 'none';
			document.getElementById('Ode_bug').style.display = 'none';
		}

		//Present Qsensor results
		if(Qsensor != ""){
			if(radio == "Easy"){
				document.getElementById('Seasy').style.display = 'inline';
				document.getElementById('Smedium').style.display = 'none';
				document.getElementById('Shard').style.display = 'none';

					var SdataPoints = <?php echo json_encode($SdataPoints, JSON_NUMERIC_CHECK); ?>;

					var Schart = new CanvasJS.Chart("chartContainerSeasy", {
						theme: "light2",
						animationEnabled: true,
		//      	title: {
		//      		text: "Sensor Readings"
		//      	},
						axisX:{
							title: "Timestamp"
						},
						axisY:{
							title: "Measurement",
							includeZero: false,
							//suffix: " Cº"
						},
						data: [{
							type: "spline",
							yValueFormatString: "#,##0.0#",
						//	xValueFormatString: "hh:mm:ss TT",
						//	xValueType: "dateTime",
							toolTipContent: "{y} at {label}",
							dataPoints: SdataPoints
						}]
					});
					Schart.render();

			} else if (radio == "Medium") {
				document.getElementById('Seasy').style.display = 'none';
				document.getElementById('Smedium').style.display = 'inline';
				document.getElementById('Shard').style.display = 'none';

				var SdataPoints = <?php echo json_encode($SdataPoints, JSON_NUMERIC_CHECK); ?>;


				var Schart = new CanvasJS.Chart("chartContainerSmedium", {
					theme: "light2",
					animationEnabled: true,
	//      	title: {
	//      		text: "Sensor Readings"
	//      	},
					axisX:{
						title: "Room"
					},
					axisY:{
						title: "Average",
						includeZero: false,
						//suffix: " Cº"
					},
					data: [{
						type: "column",
						yValueFormatString: "#,##0.0#",
					//	xValueFormatString: "hh:mm:ss TT",
					//	xValueType: "dateTime",
					//	toolTipContent: "{y} at {label}",
						dataPoints: SdataPoints
					}]
				});
				Schart.render();

			} else if (radio == "Hard") {
				document.getElementById('Seasy').style.display = 'none';
				document.getElementById('Smedium').style.display = 'none';
				document.getElementById('Shard').style.display = 'inline';

			} else {
				document.getElementById('Seasy').style.display = 'none';
				document.getElementById('Smedium').style.display = 'none';
				document.getElementById('Shard').style.display = 'none';
			}
		} else {
			document.getElementById('Seasy').style.display = 'none';
			document.getElementById('Smedium').style.display = 'none';
			document.getElementById('Shard').style.display = 'none';
		}

		//Present Qactuator results
		if(Qactuator != ""){
			if(radio == "Easy"){
				document.getElementById('Aeasy').style.display = 'inline';
				document.getElementById('Amedium').style.display = 'none';
				document.getElementById('Ahard').style.display = 'none';

			} else if (radio == "Medium") {
				document.getElementById('Aeasy').style.display = 'none';
				document.getElementById('Amedium').style.display = 'inline';
				document.getElementById('Ahard').style.display = 'none';

				var AdataPoints = <?php echo json_encode($AdataPoints, JSON_NUMERIC_CHECK); ?>;


				var Achart = new CanvasJS.Chart("chartContainerAmedium", {
					theme: "light2",
					animationEnabled: true,
	//      	title: {
	//      		text: "Sensor Readings"
	//      	},
					axisX:{
						title: "Room"
					},
					axisY:{
						title: "Number of Changes",
						includeZero: false,
						//suffix: " Cº"
					},
					data: [{
						type: "column",
						toolTipContent: "{y} " + AfieldChange + " at {label}",
						//yValueFormatString: "#,##0.0#",
					//	xValueFormatString: "hh:mm:ss TT",
					//	xValueType: "dateTime",
					//	toolTipContent: "{y} at {label}",
						dataPoints: AdataPoints
					}]
				});
				Achart.render();

			} else if (radio == "Hard") {
				document.getElementById('Aeasy').style.display = 'none';
				document.getElementById('Amedium').style.display = 'none';
				document.getElementById('Ahard').style.display = 'inline';

			} else {
				document.getElementById('Aeasy').style.display = 'none';
				document.getElementById('Amedium').style.display = 'none';
				document.getElementById('Ahard').style.display = 'none';
			}
		} else {
			document.getElementById('Aeasy').style.display = 'none';
			document.getElementById('Amedium').style.display = 'none';
			document.getElementById('Ahard').style.display = 'none';
		}

		//Present Qconfig results
		if(Qconfig != ""){
			if(radio == "Easy"){alert('window loaded');
				document.getElementById('Ceasy').style.display = 'inline';
				document.getElementById('Cmedium').style.display = 'none';
				document.getElementById('Chard').style.display = 'none';

			} else if (radio == "Medium") {
				document.getElementById('Ceasy').style.display = 'none';
				document.getElementById('Cmedium').style.display = 'inline';
				document.getElementById('Chard').style.display = 'none';

			} else if (radio == "Hard") {
				document.getElementById('Ceasy').style.display = 'none';
				document.getElementById('Cmedium').style.display = 'none';
				document.getElementById('Chard').style.display = 'inline';

				var CdataPoints1 = <?php echo json_encode($C1dataPoints, JSON_NUMERIC_CHECK); ?>;
				var CdataPoints2 = <?php echo json_encode($C2dataPoints, JSON_NUMERIC_CHECK); ?>;


				var Cchart = new CanvasJS.Chart("chartContainerChard", {
					theme: "light2",
					animationEnabled: true,
	//      	title: {
	//      		text: "Sensor Readings"
	//      	},
					axisX:{
						title: "Room"
					},
					axisY:{
						title: "Quantity",
						includeZero: false,
						//suffix: " Cº"
					},
					data: [{
						type: "column",
					//	yValueFormatString: "#,##0.0#",
					//	xValueFormatString: "hh:mm:ss TT",
					//	xValueType: "dateTime",
					toolTipContent: "{y} " + CfieldQuantS + " at {label}",
					showInLegend: true,
					legendText: CfieldQuantS,
						dataPoints: CdataPoints1
					},{
						type: "column",
					//	yValueFormatString: "#,##0.0#",
					//	xValueFormatString: "hh:mm:ss TT",
					//	xValueType: "dateTime",
					toolTipContent: "{y} " + CfieldQuantA + " at {label}",
					showInLegend: true,
					legendText: CfieldQuantA,
						dataPoints: CdataPoints2
					}
				]
				});
				Cchart.render();

			} else {
				document.getElementById('Ceasy').style.display = 'none';
				document.getElementById('Cmedium').style.display = 'none';
				document.getElementById('Chard').style.display = 'none';
			}
		} else {
			document.getElementById('Ceasy').style.display = 'none';
			document.getElementById('Cmedium').style.display = 'none';
			document.getElementById('Chard').style.display = 'none';
		}


		//Present Qrule results
		if(Qrule != ""){
			if(radio == "Easy"){
				document.getElementById('Reasy').style.display = 'inline';
				document.getElementById('Rmedium').style.display = 'none';
				document.getElementById('Rhard').style.display = 'none';

			} else if (radio == "Medium") {
				document.getElementById('Reasy').style.display = 'none';
				document.getElementById('Rmedium').style.display = 'inline';
				document.getElementById('Rhard').style.display = 'none';

				var RdataPoints = <?php echo json_encode($RdataPoints, JSON_NUMERIC_CHECK); ?>;

				var Rchart = new CanvasJS.Chart("chartContainerRmedium", {
					theme: "light2",
					animationEnabled: true,
	//      	title: {
	//      		text: "Sensor Readings"
	//      	},
					axisX:{
						title: "Room"
					},
					axisY:{
						title: "Quantity",
						includeZero: false,
						//suffix: " Cº"
					},
					data: [{
						type: "column",
					//	yValueFormatString: "#,##0.0#",
					//	xValueFormatString: "hh:mm:ss TT",
					//	xValueType: "dateTime",
					//	toolTipContent: "{y} at {label}",
					toolTipContent: "{y} " + RfieldQuant + " at {label}",
						dataPoints: RdataPoints
					}]
				});
				Rchart.render();

			} else if (radio == "Hard") {
				document.getElementById('Reasy').style.display = 'none';
				document.getElementById('Rmedium').style.display = 'none';
				document.getElementById('Rhard').style.display = 'inline';

				var RdataPoints1 = <?php echo json_encode($R1dataPoints, JSON_NUMERIC_CHECK); ?>;
				var RdataPoints2 = <?php echo json_encode($R2dataPoints, JSON_NUMERIC_CHECK); ?>;

				var Rchart = new CanvasJS.Chart("chartContainerRhard", {
					theme: "light2",
					animationEnabled: true,
	//      	title: {
	//      		text: "Sensor Readings"
	//      	},
					axisX:{
						title: "Timestamp"
					},
					axisY:{
						title: "Value",
						includeZero: false,
						//suffix: " Cº"
					},
					toolTip: {
						shared: true
					},
					legend: {
						cursor:"pointer",
						verticalAlign: "top",
						fontSize: 22,
						fontColor: "dimGrey",
					},
					data: [{
						type: "spline",
						yValueFormatString: "#,##0.0#",
					  name: RfieldRef,
					//	xValueFormatString: "hh:mm:ss TT",
					//	xValueType: "dateTime",
					showInLegend: true,
					legendText: RfieldRef,
						//toolTipContent: "{y} at {label}",
						dataPoints: RdataPoints1
					}, {
						type: "spline",
						yValueFormatString: "#,##0.0#",
					  name: RfieldRead,
					//	xValueFormatString: "hh:mm:ss TT",
					//	xValueType: "dateTime",
					showInLegend: true,
					legendText: RfieldRead,
					//	toolTipContent: "{y} at {label}",
						dataPoints: RdataPoints2
					}]
				});
				Rchart.render();

			} else {
				document.getElementById('Reasy').style.display = 'none';
				document.getElementById('Rmedium').style.display = 'none';
				document.getElementById('Rhard').style.display = 'none';
			}
		} else {
			document.getElementById('Reasy').style.display = 'none';
			document.getElementById('Rmedium').style.display = 'none';
			document.getElementById('Rhard').style.display = 'none';
		}


}); //end of load event


			</script>

			<script src="js/vendor/jquery-1.11.0.min.js"></script>
			<script src="js/bootstrap.js"></script>
			<script src="js/plugins.js"></script>
			<script src="js/main.js"></script>
			<script src="https://canvasjs.com/assets/script/canvasjs.min.js"></script>

    </body>
</html>
