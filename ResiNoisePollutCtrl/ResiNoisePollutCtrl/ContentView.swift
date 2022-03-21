//
//  ContentView.swift
//  ResiNoisePollutCtrl
//
//  Created by Cyrus on 6/1/2022.
//

//Our next step is to edit our Info.plist file to make sure it allows us to pull data from an external source. Click on Info.plist, then right click to add a new row and type “App Transport Security Settings”. Inside of that we want to add another row, (make sure the down arrow is clicked on the first row) “Allow Arbitrary Loads” and set that to “YES”.

import SwiftUI
import RealityKit
import CodeScanner

var ipAddress = ""

struct ARViewContainer: UIViewRepresentable {
    
    func makeUIView(context: Context) -> ARView {
        
        let arView = ARView(frame: .zero)
        
        // Load the "Box" scene from the "Experience" Reality File
        let boxAnchor = try! Experience.loadBox()
        
        // Add the box anchor to the scene
        arView.scene.anchors.append(boxAnchor)
        
        Timer.scheduledTimer(withTimeInterval: 2, repeats: true) { timer in
            //                let randomNumber = Int.random(in: 1...20)
            getData()
            //                if randomNumber == 10 {
            //                    timer.invalidate()
            //                }
        }
        
        func getData() {
            
            guard let url = URL(string: ipAddress)
            else {
                //                fatalError("Missing URL")
                return
            }
            
            let urlRequest = URLRequest(url: url)
            
            let dataTask = URLSession.shared.dataTask(with: urlRequest) { (data, response, error) in
                if let error = error {
                    print("Request error: ", error)
                    return
                }
                
                guard let response = response as? HTTPURLResponse else { return }
                if response.statusCode == 200 {
                    guard let receivedData = data else { return }
                    
                    //                    let responseData:NSString = NSString(data:receivedData, encoding:String.Encoding.utf8.rawValue)!
                    let responseData = Array(String(data:receivedData, encoding:String.Encoding.utf8)!)
                    
                    DispatchQueue.main.async {
                        
                        //                        switch responseData.intValue {
                        //                        case 1:
                        //                            boxAnchor.notifications.nA.post()
                        //                            boxAnchor.notifications.nB.post()
                        //                            boxAnchor.notifications.nC.post()
                        //                        case 2:
                        //                            boxAnchor.notifications.nA.post()
                        //                            boxAnchor.notifications.nB.post()
                        //                        case 3:
                        //                            boxAnchor.notifications.nA.post()
                        //                        case 4:
                        //                            boxAnchor.notifications.nB.post()
                        //                            boxAnchor.notifications.nC.post()
                        //                        case 5:
                        //                            boxAnchor.notifications.nC.post()
                        //                        case 6:
                        //                            boxAnchor.notifications.nB.post()
                        //                        case 7:
                        //                            boxAnchor.notifications.nA.post()
                        //                            boxAnchor.notifications.nC.post()
                        //                        default:
                        //                            print("Error")
                        //                        }
                        if responseData[0] == "1"{
                            boxAnchor.notifications.nA.post()
                        }
                        if responseData[1] == "1"{
                            boxAnchor.notifications.nB.post()
                        }
                        if responseData[2] == "1"{
                            boxAnchor.notifications.nC.post()
                        }
                        if responseData[3] == "1"{
                            boxAnchor.notifications.mA.post()
                        }
                        if responseData[4] == "1"{
                            boxAnchor.notifications.mB.post()
                        }
                        if responseData[5] == "1"{
                            boxAnchor.notifications.mC.post()
                        }
                        
                        if ipAddress != ""{
                            boxAnchor.notifications.scanned.post()
                        }
                        
                    }
                }
            }
            dataTask.resume()
        }
        
        return arView
        
    }
    
    func updateUIView(_ uiView: ARView, context: Context) {
    }
    
}

struct ContentView : View {
    
    var body: some View {
        
        TabView {
            ZStack {
                Color.blue.ignoresSafeArea()
                VStack {
                    Text("Scan the Host IP address with correct document suffix QR code in P.2 to trigger the 3D floor plan animation in P.3")
                        .foregroundColor(Color.white)
                        .font(.largeTitle)
                        .bold()
                }
            }
            .accentColor(Color.black)
            
            CodeScannerView(codeTypes: [.qr], simulatedData: "Paul Hudson") { response in
                switch response {
                case .success(let result):
                    print("Found code: \(result.string)")
                    ipAddress = result.string
                case .failure(let error):
                    print(error.localizedDescription)
                }
            }
            .cornerRadius(30)
            
            ARViewContainer()
                .cornerRadius(30)
        }
        .tabViewStyle(PageTabViewStyle(indexDisplayMode: .always))
        //        return ARViewContainer().edgesIgnoringSafeArea(.all)
        
    }
    
}

#if DEBUG
struct ContentView_Previews : PreviewProvider {
    static var previews: some View {
        ContentView()
    }
}
#endif
