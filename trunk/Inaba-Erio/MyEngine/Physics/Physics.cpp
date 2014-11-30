//dependencias hkBase.lib;hkVisualize.lib;hkInternal.lib;hkSerialize.lib;hkGeometryUtilities.lib;hkcdInternal.lib;hkcdCollide.lib;hkpCollide.lib;hkpConstraint.lib;hkpConstraintSolver.lib;hkpDynamics.lib;hkpInternal.lib;hkpUtilities.lib;

#include "Physics.h"

#include <xmmintrin.h>
#include <Common/Base/hkBase.h>
#include <Physics2012/Dynamics/World/hkpWorld.h>
#include <Common/Visualize/hkVisualDebugger.h>
#include <Physics2012/Utilities/VisualDebugger/hkpPhysicsContext.h>
#include <Common/Base/Memory/System/Util/hkMemoryInitUtil.h>
#include <Common/Base/Memory/Allocator/Malloc/hkMallocAllocator.h>
#include <Physics2012/Collide/Dispatch/hkpAgentRegisterUtil.h>

#include <Physics2012/Dynamics/Entity/hkpRigidBody.h>
#include <Physics2012/Collide/Shape/Convex/Box/hkpBoxShape.h>
#include <Physics2012\Collide\Shape\Convex\Sphere\hkpSphereShape.h>
#include <Physics2012/Utilities/Dynamics/Inertia/hkpInertiaTensorComputer.h>

#include <Physics2012\Collide\Shape\Convex\ConvexVertices\hkpConvexVerticesShape.h>
#include <Common\Internal\ConvexHull\hkGeometryUtility.h>

using namespace Inaba;

Physics* Physics::_instance = NULL;
hkpWorld* Physics::_world = NULL;


Physics::Physics() :
_vdb(NULL),
_physicsContext(NULL)
{
	InitPhysics();
}

Physics::~Physics()
{
	DeInitPhysics();
}

Physics* Physics::GetInstance()
{
	if (!_instance)
	{
		_instance = new Physics();
	}
	return _instance;
}


hkpWorld* Physics::GetWorld()
{
	return _world;
}

static void HK_CALL errorReport(const char* msg, void *userContext)
{
	std::cerr << msg << std::endl;
}

void Physics::InitPhysics()
{
	hkMemoryRouter *memoryRouter = hkMemoryInitUtil::initChecking(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024 * 1024));
	hkBaseSystem::init(memoryRouter, errorReport);

	hkpWorldCinfo worldInfo;
	worldInfo.m_gravity = hkVector4(0.0f, -9.8f, 0.0f);

	worldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_REMOVE_ENTITY;
	worldInfo.setBroadPhaseWorldSize(1000.0f);

	_world = new hkpWorld(worldInfo);

	hkpAgentRegisterUtil::registerAllAgents(_world->getCollisionDispatcher());

	_physicsContext = new hkpPhysicsContext();
	hkpPhysicsContext::registerAllPhysicsProcesses();
	_physicsContext->addWorld(_world);
	hkArray<hkProcessContext*> contexts;
	contexts.pushBack(_physicsContext);
	_vdb = new hkVisualDebugger(contexts);
	_vdb->serve();
}


//TEST
/*void Physics::InitPhysics()
{
	//if (!s_HavokIsStarted) {

#if defined(HK_COMPILER_HAS_INTRINSICS_IA32) && (HK_CONFIG_SIMD ==  HK_CONFIG_SIMD_ENABLED)
		_MM_SET_FLUSH_ZERO_MODE(_MM_FLUSH_ZERO_ON);
#endif

		// Arrancamos Havok con Memory Leak Detector. Leer documentación para saber mas :)
		hkMemoryRouter* memoryRouter = hkMemoryInitUtil::initChecking(hkMallocAllocator::m_defaultMallocAllocator, hkMemorySystem::FrameInfo(1024 * 1024));
		hkBaseSystem::init(memoryRouter, errorReport);

		//*********************************** COMIENZO A CONFIGURAR WORLD ****************************
		// Configuro la Fisica del World

		hkpWorldCinfo HavokWorldInfo;
		HavokWorldInfo.m_gravity = hkVector4(0.0f, -9.8f, 0.0f); // Ajusto Gravedad YAY!
		HavokWorldInfo.m_simulationType = hkpWorldCinfo::SIMULATION_TYPE_CONTINUOUS;

		// Seteo el comportamiento en los limites del world y el Size del World.
		HavokWorldInfo.m_broadPhaseBorderBehaviour = hkpWorldCinfo::BROADPHASE_BORDER_FIX_ENTITY;
		HavokWorldInfo.setBroadPhaseWorldSize(10000.0f);

		_world = new hkpWorld(HavokWorldInfo);
		_world->m_wantDeactivation = false;

		// Bloqueo el World para poder modificarlo :D!
		_world->markForWrite();

		// Detecto colisiones a travez de Havok Agents.
		hkpAgentRegisterUtil::registerAllAgents(_world->getCollisionDispatcher());

		//*********************************** TERMINO DE CONFIGURAR WORLD *****************************
		//*********************************** CONFIGURO EL VISUAL DEBUGER *****************************
		// Inicio Visual Debugger

		_physicsContext = new hkpPhysicsContext();
		hkpPhysicsContext::registerAllPhysicsProcesses();
		_physicsContext->addWorld(_world);

		// Desbloqueo el World para que el resto lo use (AL SER MULTITHREADING ES NECESARIO ESTO)
		_world->unmarkForWrite();

		hkArray<hkProcessContext*> havokContexts;
		havokContexts.pushBack(_physicsContext);

		_vdb = new hkVisualDebugger(havokContexts);
		_vdb->serve();

		//*********************************** TERMINO EL VISUAL DEBUGER *******************************

		//****************************************** LLAMO A TEST SCENE *******************************
		//StartTestScene();
		//****************************** TERMINO DE LLAMAR A TEST SCENE *******************************

		//s_HavokIsStarted = true;                                // Seteo mi trigger a True para no poder inicializar todo de nuevo :D!
		_instance = this;
	//}
}*/

void Physics::DeInitPhysics()
{
	_vdb->removeReference();
	_physicsContext->removeReference();

	_world->removeReference();

	hkBaseSystem::quit();
	hkMemoryInitUtil::quit();
}

void Physics::stepSimulation(float deltaTime)
{
	_vdb->step();

	float fHavokStep = (deltaTime / 1000.0f);
	if (fHavokStep < 0.00000001f) {
		return;
	}

	if (fHavokStep > 4.0f) {
		fHavokStep = 3.9f;
	}

	_world->stepDeltaTime(fHavokStep);
}

void Physics::addEntity(RigidBody *_rigidb)
{
	_world->markForWrite();
	_world->addEntity(_rigidb->rigidbody());
	_world->unmarkForWrite();
}


#include <Common\Base\KeyCode.cxx>
//**************************************************************
// Saco Cositas que no me interesan (Al menos por ahora)
#undef HK_FEATURE_PRODUCT_AI
#undef HK_FEATURE_PRODUCT_ANIMATION
#undef HK_FEATURE_PRODUCT_CLOTH
#undef HK_FEATURE_PRODUCT_DESTRUCTION
#undef HK_FEATURE_PRODUCT_DESTRUCTION_2012
#undef HK_FEATURE_PRODUCT_BEHAVIOUR
#undef HK_FEATURE_PRODUCT_MILSIM
#undef HK_FEATURE_PRODUCT_PHYSICS

#define HK_EXCLUDE_LIBRARY_hkpVehicle
#define HK_EXCLUDE_LIBRARY_hkCompat
#define HK_EXCLUDE_LIBRARY_hkSceneData
#define HK_EXCLUDE_LIBRARY_hkcdCollide

#define HK_EXCLUDE_FEATURE_SerializeDeprecatedPre700
#define HK_EXCLUDE_FEATURE_RegisterVersionPatches
#define HK_EXCLUDE_FEATURE_hkpHeightField
#define HK_EXCLUDE_FEATURE_hkpAccurateInertiaTensorComputer
#define HK_EXCLUDE_FEATURE_hkpUtilities
#define HK_EXCLUDE_FEATURE_hkpVehicle
#define HK_EXCLUDE_FEATURE_hkpCompressedMeshShape
#define HK_EXCLUDE_FEATURE_hkpConvexPieceMeshShape
#define HK_EXCLUDE_FEATURE_hkpExtendedMeshShape
#define HK_EXCLUDE_FEATURE_hkpMeshShape
#define HK_EXCLUDE_FEATURE_hkpSimpleMeshShape
#define HK_EXCLUDE_FEATURE_hkpPoweredChainData
#define HK_EXCLUDE_FEATURE_hkMonitorStream
//Fin Cositas que no me interesan :)
#include <Common/Base/Config/hkProductFeatures.cxx>