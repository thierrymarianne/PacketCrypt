#ifndef POOLPROTO_H
#define POOLPROTO_H

#include "packetcrypt/PacketCrypt.h"
#include "Buf.h"

typedef struct PoolProto_Work_t {
    PacketCrypt_BlockHeader_t blkHdr;
    Buf32_t contentHash;
    uint32_t shareTarget;
    uint32_t annTarget;
    int32_t height;
    uint32_t coinbaseLen;
    uint8_t coinbaseAndMerkles[];
} PoolProto_Work_t;

static inline bool PoolProto_Work_isValid(int totalLen, PoolProto_Work_t* work) {
    if (totalLen < (int)sizeof(PoolProto_Work_t)) { return false; }
    if (totalLen < ((int)sizeof(PoolProto_Work_t) + (int)work->coinbaseLen)) { return false; }
    if ((totalLen - (int)sizeof(PoolProto_Work_t) - work->coinbaseLen) % 32) { return false; }
    return true;
}

static inline int PoolProto_Work_merkleCount(int totalLen, PoolProto_Work_t* work) {
    if (!PoolProto_Work_isValid(totalLen, work)) { return -1; }
    return (totalLen - (int)sizeof(PoolProto_Work_t) - work->coinbaseLen) / 32;
}

#endif


/*
09f91102ffff0f201d905285b9e42b69d471e1aeb4bcce6bd4c6566c1ea851fd8c57e068b8c561b81d35000000000000000000208da813d11144f96902bf42d3bdda09b79a9f1d05153d77be8700000000000000691289dc1cb0fdccbc25b577104d58e26cdbf5c78329c9e3ed930cd8fb09ff6f72d8b85c841a011a00000000ca7f0500b8060000002b000006030000ffff0020d5ba16000000000000000000e70ce0b936695bfffcff723c66338e985fcff78bce06371fa67354a17d9af597f61b4a41a30ff138d07162f8b6158d860746428032f2fed95d992f165701ef45a1aa8363324e75441017800dfe342796514f2ae1dff92694c093e1e85210c553168b1bb804cb344b89e2a78b96a9b00a8d61f8de036a4aa06bcf8801863a7f2e60494831b42c2491613c8058e8f252ad75190fc0520a015afed1477f3c2aa3546635a9aae9814a93b1729edeffdae918e3e48530ef1cf4dd802854b4d6ff41d6b94a698c4557c9b7963ca292315b89a38ec180cf5a1c5ef1d06ca8ef4273fd7d5ee49df42d5308d7888adea32f93a695a4aca951d090ebbbc02a2855298c4aa6baf41356041510a212c64250423d85ea4fd864e3ee281067ff59c4e155c225ee3c45b5db5c0f252684bffa3e34eb37137583c785dee9941f98ce9ba9dc3ad6c9e64876f0d9275d51648ebf839c8c256123b6820cc116584b6ef43110ee34a7f25597254582878c4e89c54a89cc8050ca0529a509682b505c2c16d58b3497bdf4d07ab8f58381626ee7d9ca00d1a1ecb94f7e785ca4f8155218779cf17379c33594a5de383642f39575c35e4243ca3a4febab42604daeb462a98a79e940db55408eee0d8ae879879188034c5328fb5fd20b9436ff855ffc4447720fa18052b32c500f62caf9941181fecb635d4d86727eb2f60e9c1eb40077a770c6d6f70665cf7a3e9813f585900f07efb1b358b5cfdc43ec533184a83a3dc5374bc7bc36bb8b4cba67dbb3000a3c3397d641d8bb7a98eb7673b8b8e03837407805327a6035bc6410a99fa60c10c95ab333f9c3dd6304a12a06992b2927648aee98f43c9408941653844f9e69eaf9ebec43001b403efd25b5b6103c83e718edbd721cac28a4aabf6d5bc47c37db20477089f59c84e7059198fd312d8759ccea198b958158555fda7751d3d2def778a86f176bdb35bc660ddeaaa06f4e7e3e4d6f0df38c7bf25dc940a7a848ff0a85f8813c52e17b8b63f47cfacd27e649af633faf868900aed269fad49d2647a94cfdd9f87f698f3feaf307c5d9ddb55b897d7af1c03a2c045a3e4524ac391fe5503936af38a89ac8deeecfe02cc05681a177727bf507e63bf52aadfa129fb6411c2e58ee32f26ddc5d420ddd1a21e765efac94123c65b7c57a51f5dab5e184485b025807cd497bb6e2678114c72858d1b95af23de03f32527d19274dd85df58e5d8ecc8ce9e5ef1d5b035cc883fda2413665020bf6657dd0a10e69ff648f8a94b941119bd3792eef457492644e45e236e5878e27ef43fb7b5119035ccf1c07be900a7b61d6fa7319d7729dda1cd36bb8b74d810bf60682239bc4cfe94fc25cf83bc8d1f7c873908b1bc5ff5d1a0a8cceb436e41a1605fed77f068c5a4956268a94004e0600ac090000ffff0020d8ba1600000000000000000069e25fc42d4824190767f27ccbf58f0a5e31a087f4149efeffdf809fd4e18a16970f09f7440a9b45496f2afb69cbab570bb032e35462eb0b5d8befd795b31787a664abf4e0e5b0122e514a13f12db937adae23cab647995dd453321c8eba70026b75fa9caae9f7dc3df9133e5f5e7b08a8b67f9d5da920ed06ca4fc977257561f4531cbdba702d5f7473728f7f20754caf9e9bad89176c54b5894947534dd847731089ea870bc400560a18535b6fd52782640f5121cac3dbe5261c462c32ab48e5f79f5ecea1c87a93e3d3bd71e216c776862d319d6d03f422d94ebb36593493881cc1b002329fd02e6387ab8e84ffbcec1b1191f392a387de3fe372f7304adc11bd104fd5563dc72a929f5fcc9985e217841738b401766470ed1f9180df677aaf71b55adfd930c2613a46e2d4ec92a9d57c95cba705ef477c435924e6cea1d130772e026e911ce6226296966b02ca61c239420c1ef89dfceea098280b35248be82b0f20b457993fdab5791145f246958bedca39c1bc5f06feffeba5fbac6f3fb7aabf8fa271bc1010b2a8eb8f7e522d9d8eba82966799a45935b0202ff78cf59bd18aafc6afc3cff6b40a4fd5ec0e8143b9965941d7bc71f311488e0904f6b8afa089a5c1532541d128c45d868655ca335ad767aa1f121630535a60f7ffa57d9d2e00f09e70dbb18255b95fbc029949b7a98f9916e0274e8bc7868b42524aed0f1017df3c8b4d5666bae35ee06ca1ba132f9816d1ef92bc7782486b1543aaf84fdaf044bd3f9814eb7da0e755230e28247c94a2c1277961bccb0b527fbedd6e92d42eeb0db987ce16db2e791efe3bb15e67e617ba94263671f21b1573b45a63dbeeec6338bed5d4b2e428b826ce94f9e218486cbb1b6b09ac7db3b1521b5bb1408d13b1d439a8fa71840aec77a6adfd722a74450db9dac48e60a3a7344f2f5c97202db303f61a8b32c7cae1c6644d8146781037d17b662d214d954a83df242eb1dc0afecb423900e84f3c569f7365ab36f9430696f9d2fe6ad27f2af719cdf58b80ff5d723dad18697b1990a4c3612721f6050bc754c2f43a53a2eaa865422a3f44eb5f2cfb788793b7ffc86fa213a06cf384b368d3c94607307c1592853e4e0f3b67974c5df92f769c8baf32037d57f3a7c73f884d209126a73f93bc5dce79ced3cbf6a130657c6f74b636f605b6ada8d66a79eafbcf7c5299a3c194ffe0f1a78d9e6dab21edadefad1cb0fe345d174801dd604037906e29b070065fdc18aad065e426d86c8fed333c5f8697dca23c0c0e8db9fa89973b225357ededb3e60631d82d7c37f7357e37aa2ab55175bcb0353a334e55a9e33bfa049bffefbd83b33b64ca54b9adf4bad578c7d30b290df5b73f1f7881e863e60cecd874b524254a495af9097fe3d489007d0700f0090000ffff0020d8ba1600000000000000000069e25fc42d4824190767f27ccbf58f0a5e31a087f4149efeffdf809fd4e18a1664c9280600926133700dbe0ae52a3b8561e625112a44e2aa638d3d497f5c11d1f0cf0d751562bf3be1466baa6646d8b1699842a2e7f9b102447a2cb1a4d51854f434433cb37f929972d13330350726ff07682497b0553f013709e173c433fc63acc34920db12731d2bb7f8475b8f9ad7447189ccf787737a946d0ae4c791e2f861e6ac44a38ee3e783a37aa587e6b76fa94c7f4d2961f1057ee3037b6741bcc2f439c8e6c07f94f5d10d3ac856f82649e402a050fd66fd9ffc8da83f431f8fe666021246029bbd3a8eb4f65b3711ea54b04ad75a08d3ebed484e0da3ada897d649d7c0ce8db9525321db55d6e8a9c55b4bc819980ed9c84aa65e5127d9129524cbe067300f5a6f5944257c64dab9af02bcc82b62a129abad3fd43857c0352930b9b683145d17b4c07760283a95969a2894478699deaf675254048f7a57b256ff2b10db9ac96e07f5e99f4b8354ecb3ee9999d3baf6b4b3116d17ad41037696af0c0f759a08f95fb0671cb3a5249b409c408c0be946a61193632309c37387b41db13e3283db76d0a448a1acc3bd47123338b3cca412b4c3ca162a014212b84b1c5ac283fbf7160e3f93c0468b0461c91b9d3c68e04f616faa38cf479b54e25186c80b6a6256f340cb467daa8c486bd710d99a3f8afe4454e107a96474b0b2b13e8f672593c67bac2c53d3126e758536b12ecd24b5686bc93d6488ccf231a68b9bc6e24da46f7247bb7ad3ca94101ae6e9e86996b115148ce33bca20d82c2bbd87800126b17f3ff2a53ebe10d7b151b5168d2b708bfbdd4d54514e8ea3427cde4bea7d3cf8e43da1d0eae2f74065865eb537f0cfc146c528eb93599b3db8032d40a1aad9bd3c4cb888a31fa1c1427f6a31c73975426b6b2044a3f38b6499537817897fd66b8eb40c66359ee0ea0ca603c862a9fc80490f7e70c0aea8cc0a993e6810547aab73a031e3d8d3ab9bbe32d5d7467a966363ab0beafbd97fda1ca2fad3a32fe97c416557ea39257e27bb8463914d6e9647e0bf056e756151b8d06e2dd56b844be0ba1879470b03c478ba0bfb525ce68ca157f579c31e6f235f5018063a3684b809a338b3650d97f3bbc62163197a5a7bd21d3aa25acae8c89a8393a0115b2f9a69e501da0f3c5ffd67dbf97b5b505abb9c1c2f50ad2b83f9888120fb3c448eb962c8a053d1c67613310e76b788c5c5ef85432c1a35ae1baccbb9f2f2e4edb2612cafe2cd0fb0976034e1887c341e3ff81f478dffa7c9588de472045d99571aa56431ab3685675c022144d228f20fd2ce4837f6a112e6cfbabcc2e0e2d5e54c2df8f73c5dbe1e230290b08ce5bda5d8652f9e91ff85affea736ec9561ee00ef204776065ac30093090023030000ffff0020d5ba16000000000000000000e70ce0b936695bfffcff723c66338e985fcff78bce06371fa67354a17d9af5978f47171b82171d4a58e62ffb97db21ac668137a74591567341c92ef18e63ef384d66393fef93a4f06e6c1c60e0004e2a1cab0d8ac4d1e1834ce398479a09fb1c7fdc87314da372b675dccb9c62543e0619e439ce326a44546ab7ff232ebe5552aabee2473b669fde52b3e73ff21c46efe1c0ee0781bba70c548fabe385418f2850fe890acbc101a143652fb2b0625642008ac1de4167fc0adb9fb4b2921f28e058c08c0c09952aadc4419bda74e311d0e848ac140d7cf9af6b52325a8d84466a082254ec6ab19bc3273a6528a13ea954c34bb9fdd9af5e26dd5406df82c148d44c564ba5fdcafa1afa37ac4dce1f8fa4c681d81c7e4078c6d0732b6be89bab560766529f69813d95689fe776dc1658fe07be7dbee30070045a1f4eab3933606e105c1ec3b20c85248927b6a7e7619b40a7e411aed2789df5871fa750cd5af415be5d3af65e00a011c928e4e60d4803cf39359d4cdb4baf663f47059f6d8d99b3202f1709227bc9c281b916efbb4f82886bb582c3dad0c5074fae6892b906a067a4d4339436a5945323df61ecec0422f0f7c3ab5959bd1c427a1badd6ec742389c6a657e32056a5a0af038da70e10a8ee09170311afee0915feef4aed7f1f9946bb2d0a9394677bdb430dd84d0f5e5e22569791596ab5f370a3e289d4bfefc6c8b322c925c4b17a79152c51ea651520d6488b884422dcb31491ae6ebf460e40a95d2c8ce9a12a9882fd8cb8f167efacc0e03969e6fd383c45e05fa6a1c878946e27aeca20027596cf72e3db527fd0e1e725d18b8c9efbb469d6d3bd7f619feab26d61f0f8cc91115d385ee9ebc376e14cc35f5eb6578203c2990d64a7784a94684d578c357f52b7ed11dc8e99bf5c3cbb01060827e97ab5775ebc8f8b3376bc7299f1dd8968b6123f64cbfb339c6ff844b38737da145c7b95fafa835cd0c9698170b719d8722644e07a5161383b2b7bc29f66080ae4d79c00ac081b503149d9fb60890dd89ec125b10227e82f5e221e577c7c674bcb01a90bead480a89a036ccd494f7949648c8156e6a18b86b82a37305613e3e60d892bc1c44b7beedd4a75b05f83934e78c6a88fb7cbb65b4af861659eb3a7f103b55a57641a838b58e2d4c2422b69639a511e3ed69a8cb073205af20c3b86ced1bafcb478066f9e19fc2260442be113265d936e52035a16f3ff69cc910da50baf8107875a21ac82e4ec5ba6c269e36d123859cdb97f416433cfebe8957936496aaf0cdbbabf6766440c74e2201d67cf3f7615c7b33ecca96253c6bb0a97809d8f623239ce9d79fc7c337955a1ad5d39af1b74a1753671dcd544a85d976f7602f642f802524d5f8832ba21ecf091ce4a1be7eb9fa1bb271bd6a2841392830cf05e2c150b01294d2d7c736fa30a279a013ee82a5299505de36de6ad71840e32342f94c4043aad8e96b69ca35f8e9bc12e72c41de80d50d07bcaa5c773e439c8741a533aaad378f97197c271026a012dc28690ee170d6554c2a7710f31b385561925915a196659d077bc008dd458c37f3de5ac3000ececd7e7611ba097ec3031f501706efdd19f340a265e02f58d23b4172a4985c05f8e5679c69d0d00624608c6f663307ae8cdf657a62e307f0917d1398c94be7f7a35a27f3c15b9a7af9429784844f91a4daad16af80fc2dd0e49ba4c302c6f4fee93e0ef44334916cc2c9819a16c0300c8d38368cbff04008f4412fd72e2162965e45a1509ac0d24c313a37817f2e463ed9fe8ca98ba304ce7f84edfe4883100388807bd9d358618c1601ddb5a413fd978effb8d09f490e3ab154f2821074cd58691ca6bf74595000fa5ddf87ff82017169b371ee973cfd8418b8fc4a36b0b14466370d627b53fc56ba716cdd5aa0b01154a239bf0ad493a1af2ef00ee91cc609644c947cf57b028e6c0be409c66ad1a859050148005870597fb38c3a1db43d5e60229df8453366ce1534d7904e26e8972ad1161a326b936abf072cb86de7302302aa54969800f7de3abe553cf61639f0aca485ebf2f2559fa48400888da4390da671757d5f50e00578ddae2e795b886423446d730d57047a35c947b297a3ad9be93813bf379d11db4f174f900f7e324e5b48c3595dec3702ed61942258bba48c1b7f7f6d00e63c0ffee122b96df0f00778a24103f420d00ebcff3b4301041cd1c5a2d89f7d2172c223c8e622563d207a0923c564aea66a3056e56271f49160081d56bad0e4035b4c7966ee2c598c53b09600412b0eeccb9a603c0aed54e265466b83b240d6449004b3a32390ad4d25fce62bb48a1acbd30e26b8843ff71d25291613595dd61fc4528d838b6a43ca700f678351c6ca1f159e3c2243a3e7df835abed7704dab56c25fd32e061f889cca2eb261a49933734015bdbbfafac091ac937b01ceaa235ae3919f3b65ab39b6a218083adaa3ceeaf30a44cebe531ccee127555e23210099813e15e4061524f5a755b1f4e5a00f1a1b0d1cb0f5e920c9b831ee897dedd21650946818628638c344e9f640150a66e2ddab79c26927f16f9f481cbd67224bb62830852822f43de6b02bcb21263ecca4473f1151a27d08b36e9b5d5d1422a391fc4e6127615af40098eefbf652a1c703f015ed8d0b6a4775bed23e82460c5edda57590293a3f4ff98848f25abc5479418c482b7e4d78e3ec800e8254e23b395f41903092c3aa8effe4e82f283d956710ae13fe74244d0170f788617df9799561f0076f86ad1a9acffd671bf11c5a8da9fe05752ad22e914dc5c9ced06b41eee896b529c6eae80de0c007ca4b17d523447afd7309ad62c4b309a5ab405693870095ef6b5337146bb0f3118db061f78f63248ed301a1deda39c53d72496db94ddf06c71c4dfe85b8ecb707862e884604e05005f7ce1210fe91600ce818364bd698d7c4ca439f35008189ab8ab4329b94aba2f1fcfd0e18f11864037bd082d57b238009b13df648e20624843c7db0e7e51f9e03fb39bddf08746514b7b5911ec879a2d123c542518d18004210621bb036b17993458e2f7d903990bf9171aa5d14885deb178554d1b930cb68124eedf473c4713d0d4f30307db50532487008af6ef22260a444a6d8f7b907990feecc887e58d13c43f2a9428459509ff2970605530884ca228db46a20aef7e0e477b2e2b1dbe5573da296886a750d6d81ed4d17be70105ef9ad5f5ca8d4c7e971cee4583d4124d0bf10ac7cbd0923a5d1c3c51d353ed2adf127fa9eeafb0022f683d02da1749c7ae1be9f9cd835e3a8caf265beafaa05fb45cfeb5aa7b4afea67024084174b1005ded1d4074d92e1126871f44aed314b9fcae906097b721f92bafd6f952377ab913df4d39617546004a4fdd421341503a0a234e59f8f157e1dba95da363e0bac559a7550b73467e6c25b54e5dbff21800360c2760b76239b60ab2614e428be028aa7277777d44534313b44401760b017b2e0c414fccf91600a97904ac899f96300cf84c941d81ff6bc99687a16616cf3f880f730591b5b6edb5b02ae876a1c07227c14cf33711df10b21ed5cfb361dc3b27e483ca4a3a0e47edc977922225000013747d3a75fc1900b93fd1bc87a7a3796bdb9d01edfb4c02efe7c0ec8026c51379dcf3241068560a8cad6affc24c2001a09010682fd9d29ca19f9d3bda5bb841806ff6f3a0b86e38c59295f299340cd941bbc1785a8ce4272f2ee78d61ed07aaaa661c7c36969f2e51afa6e3ea161fc5405fb783d0adc30791ecd5cd3cea1c645a1fda695380ec29dc1b0249808e022cdfebc5a13e1fd81c747e9709bc8eae51
Uploading shares [./blkmine_data/wrkdir/shares_1.bin] [0] to [http://localhost:8083/submit]
Pool replied with error 400 {"result":"","error":["announcement [1] invalid content hash want [a9620c28e6c9a760b488d01a5259295977abf64a3f603f03f087749766088ab9] got [69e25fc42d4824190767f27ccbf58f0a5e31a087f4149efeffdf809fd4e18a16]"],"warn":[]}, stopping
notgay:PacketCrypt user$ pcblk: Stdin is nolonger connected, exiting



0000002002a076b1ea30f0a9b74dff0be4e5ca85be31e6adc9a7a8eca500
0000000000002468d016b9e5d981a3514c27410db97d08c530a6eb5a405e
e901f8c6cbcf269ee283b85c841a011a0000000069e25fc42d4824190767
f27ccbf58f0a5e31a087f4149efeffdf809fd4e18a16ffff0f1fffff0020
d8ba1600d800000001000000010000000000000000000000000000000000
000000000000000000000000000000ffffffff1103d8ba16000b2f503253
482f627463642fffffffff048f0e79000000000017a914a30c149c2c5bd5
3ef9410c86b05c1374ca3b284187864ddd01000000000151000000000000
0000266a24aa21a9ed7f7cb8a3003c3f22c802ce7e00fb0ef1199c751aea
68914d25345abc2a1fc8e50000000000000000326a3009f91102fcfcfcfc
fcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfcfc
fcfcfcfcfcfcfcfcfcfc00000000bebfe9902ed70958b7f8e1bab25209ef
9daadef76d9d4bf6f97b4e6e2aa3b32919b7839dd4a06355c9119a8dedca
bf680f6967e1bf1c9b4407a246670418644555d413d486c4973efad37fe3
0b23ae55f08eb5fb1a17b397341f920def6324edab4cb817db6cdbc75de6
cdac327eba45734d1f98e1522d1f768340a2cad6557a

*/